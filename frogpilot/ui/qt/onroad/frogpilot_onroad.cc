#include "frogpilot/ui/qt/onroad/frogpilot_onroad.h"

FrogPilotOnroadWindow::FrogPilotOnroadWindow(QWidget *parent) : QWidget(parent) {
}

void FrogPilotOnroadWindow::resizeEvent(QResizeEvent *event) {
  rect = QWidget::rect();
  marginRegion = QRegion(rect) - QRegion(rect.marginsRemoved(QMargins(UI_BORDER_SIZE, UI_BORDER_SIZE, UI_BORDER_SIZE, UI_BORDER_SIZE)));
}

void FrogPilotOnroadWindow::updateState(const UIState &s, const FrogPilotUIState &fs) {
  const SubMaster &sm = *(s.sm);
  const SubMaster &fpsm = *(fs.sm);

  const cereal::CarState::Reader &carState = sm["carState"].getCarState();
  const cereal::CarControl::Reader &carControl = fpsm["carControl"].getCarControl();

  showFPS = frogpilot_toggles.value("show_fps").toBool();

  if (showFPS) {
    static float avgFPS = 0.0f;
    static float maxFPS = 0.0f;
    static float minFPS = 99.9f;

    if (avgFPS == 0.0f) {
      avgFPS = fps;
    }

    static float alpha = 1.0f / (UI_FREQ * 60.0f);
    avgFPS = alpha * fps + (1.0f - alpha) * avgFPS;

    minFPS = std::min(minFPS, fps);
    maxFPS = std::max(maxFPS, fps);

    fpsDisplayString = QString("FPS: %1 | Min: %2 | Max: %3 | Avg: %4")
                          .arg(qRound(fps))
                          .arg(qRound(minFPS))
                          .arg(qRound(maxFPS))
                          .arg(qRound(avgFPS));
  }

  update();
}

void FrogPilotOnroadWindow::paintEvent(QPaintEvent *event) {
  QPainter p(this);

  p.setClipRegion(marginRegion);
  p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

  if (showFPS) {
    paintFPS(p);
  }
}

void FrogPilotOnroadWindow::paintFPS(QPainter &p) {
  p.save();

  p.setFont(InterFont(28, QFont::DemiBold));
  p.setPen(Qt::white);

  int xPos = (rect.width() - p.fontMetrics().horizontalAdvance(fpsDisplayString)) / 2;
  int yPos = rect.bottom() - 5;

  p.drawText(xPos, yPos, fpsDisplayString);

  p.restore();
}
