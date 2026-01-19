#!/bin/bash

# OpenPilot/FrogPilot Compilation Test Script
# Run this in WSL to test local compilation

set -e  # Exit on error

echo "========================================="
echo "OpenPilot Compilation Test"
echo "========================================="

# Navigate to repo
cd /mnt/c/Users/riddl/CascadeProjects/windsurf-project-3/opAIO
echo "✓ In directory: $(pwd)"

# Fix git ownership warning for WSL
echo ""
echo "Fixing git ownership..."
git config --global --add safe.directory /mnt/c/Users/riddl/CascadeProjects/windsurf-project-3/opAIO
echo "✓ Git ownership fixed"

# Ensure release/files_common exists (required by selfdrive/modeld/SConscript)
echo ""
echo "Ensuring release/files_common exists..."
mkdir -p release
if [ ! -f release/files_common ]; then
  : > release/files_common
fi
echo "✓ release/files_common present"

# Check current branch
echo ""
echo "Current branch: $(git branch --show-current)"

# Update package lists
echo ""
echo "Updating package lists..."
sudo apt-get update

# Install build dependencies
echo ""
echo "Installing build dependencies..."
sudo apt-get install -y \
  build-essential \
  clang \
  git \
  curl \
  libffi-dev \
  libssl-dev \
  libbz2-dev \
  libncurses5-dev \
  libncursesw5-dev \
  libreadline-dev \
  libsqlite3-dev \
  libzmq3-dev \
  llvm \
  tk-dev \
  python3-dev \
  python3-pip \
  libcapnp-dev \
  capnproto \
  libarchive-dev \
  qtbase5-dev \
  libqt5svg5-dev \
  libqt5serialport5-dev \
  qtmultimedia5-dev \
  qtpositioning5-dev \
  libqt5location5 \
  libusb-1.0-0-dev \
  libblas-dev \
  liblapack-dev \
  gfortran \
  scons \
  gcc-arm-none-eabi \
  gcc-arm-linux-gnueabihf \
  opencl-headers \
  ocl-icd-opencl-dev \
  libeigen3-dev \
  cython3

echo "✓ System packages installed"

# Install Python packages
echo ""
echo "Installing Python packages..."
pip3 install --break-system-packages --upgrade pip setuptools wheel
pip3 install --break-system-packages scons pycryptodome numpy pyyaml Cython pycapnp pyzmq casadi

# Create cythonize symlink for Ubuntu 24.04 compatibility
sudo ln -sf /usr/bin/cython3 /usr/bin/cythonize

# Fix Windows line endings in Python scripts
echo ""
echo "Fixing line endings in Python scripts..."
find . -name "*.py" -type f -exec dos2unix {} \; 2>/dev/null || true
find . -name "lat_mpc.py" -type f -exec dos2unix {} \; 2>/dev/null || true
find . -name "live_kf.py" -type f -exec dos2unix {} \; 2>/dev/null || true
find . -name "car_kf.py" -type f -exec dos2unix {} \; 2>/dev/null || true

# Fix shebang lines to avoid Windows line ending issues
echo ""
echo "Fixing shebang lines..."
sed -i 's|#!/usr/bin/env python3|#!/usr/bin/python3|g' selfdrive/locationd/models/live_kf.py
sed -i 's|#!/usr/bin/env python3|#!/usr/bin/python3|g' selfdrive/locationd/models/car_kf.py

echo "✓ Python packages installed"

# Show versions
echo ""
echo "========================================="
echo "Installed Versions:"
echo "========================================="
echo "Python: $(python3 --version)"
echo "GCC: $(gcc --version | head -n1)"
echo "Clang: $(clang --version | head -n1)"
echo "SCons: $(scons --version | head -n1)"
echo "NumPy: $(python3 -c 'import numpy; print(numpy.__version__)')"

# Start compilation
echo ""
echo "========================================="
echo "Starting compilation..."
echo "Using $(nproc) CPU cores"
echo "========================================="

START_TIME=$(date +%s)

# Run scons
scons -j$(nproc)

END_TIME=$(date +%s)
DURATION=$((END_TIME - START_TIME))

echo ""
echo "========================================="
echo "✓ Compilation completed successfully!"
echo "Time taken: ${DURATION} seconds"
echo "========================================="
