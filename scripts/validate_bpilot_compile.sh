#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null && pwd)"

MODE="${1:-}"

case "$MODE" in
  097)
    BRANCH="bp-BPilot-BANNABLE"
    SOURCE_BRANCH="Z-Tweaks-2025"
    SPARSE_PATHS=(
      .clang-tidy
      .dockerignore
      .editorconfig
      .github
      .pre-commit-config.yaml
      .python-version
      Dockerfile.openpilot
      Dockerfile.openpilot_base
      LICENSE
      README.md
      RELEASES.md
      SConstruct
      SECURITY.md
      body
      cereal
      common
      docs
      frogpilot
      msgq
      msgq_repo
      opendbc
      openpilot
      panda
      prebuilt
      pyproject.toml
      rednose
      rednose_repo
      release
      selfdrive
      system
      teleoprtc
      third_party
      tinygrad
      tinygrad_repo
      tools
    )
    EXTRA_COMMITS=(
      6d433e8477287b133dbcb0e42e0d9d481ebfad21
      97613232de710e2abbc16dd9403aae8922aae8da
      cb334c81d326ba3726f7ba01bec30f3d04559928
      28144bfbc48362771d138841e430879af15a4ea0
      19cfa999d97c70c92a5aca59827a020581111b5d
    )
    ;;
  0103)
    BRANCH="bp-BPilot-BANNABLE-Testing"
    SOURCE_BRANCH="Z-Tweaks-Testing"
    SPARSE_PATHS=(
      .dockerignore
      .editorconfig
      .github
      Dockerfile.openpilot
      Dockerfile.openpilot_base
      LICENSE
      README.md
      RELEASES.md
      SConstruct
      SECURITY.md
      body
      cereal
      common
      compile_commands.json
      conftest.py
      docs
      frogpilot
      launch_chffrplus.sh
      launch_env.sh
      launch_openpilot.sh
      mkdocs.yml
      msgq
      msgq_repo
      not_vetted
      opendbc
      opendbc_repo
      openpilot
      panda
      prebuilt
      pyproject.toml
      rednose
      rednose_repo
      release
      selfdrive
      system
      teleoprtc
      third_party
      tinygrad
      tinygrad_repo
      tools
      uv.lock
    )
    EXTRA_COMMITS=()
    ;;
  *)
    echo "usage: $0 {097|0103}" >&2
    exit 1
    ;;
esac

DEFAULT_TMP_ROOT="${RUNNER_TEMP:-${TMPDIR:-/tmp}}"
WORKDIR="${WORKDIR:-$DEFAULT_TMP_ROOT/manual-bpilot-$MODE}"
HELPER_SOURCE="${HELPER_SOURCE:-$SCRIPT_DIR/compile_current_branch.sh}"
CLONE_DEPTH="${CLONE_DEPTH:-200}"

run_with_retries() {
  local attempts="$1"
  shift
  local try=1
  while true; do
    if "$@"; then
      return 0
    fi
    if (( try >= attempts )); then
      return 1
    fi
    sleep $((try * 2))
    try=$((try + 1))
  done
}

git config --global user.email "55640145+BRid37@users.noreply.github.com"
git config --global user.name "BRid37"

rm -rf "$WORKDIR"
mkdir -p "$(dirname "$WORKDIR")"
TMPDIR="${TMPDIR:-${WORKDIR}.tmp}"
mkdir -p "$TMPDIR"
export TMPDIR
export TMP="$TMPDIR"
export TEMP="$TMPDIR"
run_with_retries 3 git clone \
  --no-checkout \
  --depth "$CLONE_DEPTH" \
  --branch "$BRANCH" \
  --single-branch \
  "${SOURCE_REPO:-https://github.com/LowkeyNEXT/opAIO}" \
  "$WORKDIR"
cd "$WORKDIR"

git config --global --add safe.directory "$WORKDIR"
git config core.symlinks false

run_with_retries 3 git fetch \
  --depth "$CLONE_DEPTH" \
  origin \
  "$SOURCE_BRANCH:refs/remotes/origin/$SOURCE_BRANCH"

for commit in "${EXTRA_COMMITS[@]}"; do
  run_with_retries 3 git fetch --depth 1 origin "$commit" || true
done

git sparse-checkout init --cone
git sparse-checkout set --skip-checks "${SPARSE_PATHS[@]}"

git checkout -B temp-branch "origin/$BRANCH"
git reset --hard "origin/$BRANCH"
git clean -fdx

if [ -f ".github/workflows/auto-cache/action.yaml" ]; then
  git update-index --assume-unchanged .github/workflows/auto-cache/action.yaml
fi

COMPILE_COMMIT="$(git log --oneline --first-parent --grep "Compile FrogPilot" | head -n 1 | cut -d " " -f 1)"
if [ -z "$COMPILE_COMMIT" ]; then
  echo "Compile commit not found" >&2
  exit 1
fi

COMMITS_AFTER_COMPILE="$(git rev-list "$COMPILE_COMMIT"..HEAD | tac)"
if [ -n "$COMMITS_AFTER_COMPILE" ]; then
  while IFS= read -r commit; do
    [ -n "$commit" ] || continue
    git revert --no-edit "$commit"
    if [ -f ".github/workflows/auto-cache/action.yaml" ]; then
      git update-index --assume-unchanged .github/workflows/auto-cache/action.yaml
    fi
  done <<< "$COMMITS_AFTER_COMPILE"
  git revert --no-edit "$COMPILE_COMMIT"
else
  git reset --hard "${COMPILE_COMMIT}^"
fi
if [ -f ".github/workflows/auto-cache/action.yaml" ]; then
  git update-index --assume-unchanged .github/workflows/auto-cache/action.yaml
fi

if [ -n "$COMMITS_AFTER_COMPILE" ]; then
  while IFS= read -r commit; do
    [ -n "$commit" ] || continue
    if git cherry-pick --strategy=recursive -X theirs "$commit"; then
      true
    else
      if [ -f ".github/workflows/auto-cache/action.yaml" ]; then
        git add -u ':!.github/workflows/auto-cache/action.yaml'
      else
        git add -u
      fi
      git cherry-pick --continue
    fi
  done <<< "$COMMITS_AFTER_COMPILE"
fi

for commit in "${EXTRA_COMMITS[@]}"; do
  if git cherry-pick --strategy=recursive -X theirs "$commit"; then
    true
  else
    if [ -f ".github/workflows/auto-cache/action.yaml" ]; then
      git add -u ':!.github/workflows/auto-cache/action.yaml'
    else
      git add -u
    fi
    if ! git cherry-pick --continue; then
      git status --short || true
      git cherry-pick --abort || true
      echo "extra cherry-pick failed: $commit" >&2
      exit 1
    fi
  fi
done

mkdir -p scripts
install -m 0755 "$HELPER_SOURCE" scripts/compile_current_branch.sh
./scripts/compile_current_branch.sh
