#pragma once

#include "starpilot/ui/qt/offroad/starpilot_settings.h"

class StarPilotVehiclesPanel : public StarPilotListWidget {
  Q_OBJECT

public:
  explicit StarPilotVehiclesPanel(StarPilotSettingsWindow *parent, bool forceOpen = false);

signals:
  void openSubPanel();

protected:
  void showEvent(QShowEvent *event) override;

private:
  void updateState(const UIState &s);
  void updateToggles();

  bool forceOpenDescriptions;
  bool started;

  std::map<QString, AbstractControl*> toggles;

  QSet<QString> gmKeys = {"GMPedalLongitudinal", "GMDashSpoofOffsets", "LongPitch", "RemoteStartBootsComma", "RemapCancelToDistance", "VoltSNG"};
  QSet<QString> hkgKeys = {"HKGMakeDashStock"};
  QSet<QString> longitudinalKeys = {"FrogsGoMoosTweak", "GMDashSpoofOffsets", "LongPitch", "RemapCancelToDistance", "SNGHack", "VoltSNG"};
  QSet<QString> subaruKeys = {"SubaruSNG", "SubaruSNGManualParkingBrake"};
  QSet<QString> toyotaKeys = {"ClusterOffset", "FrogsGoMoosTweak", "LockDoorsTimer", "SNGHack", "ToyotaDoors"};
  QSet<QString> vehicleInfoKeys = {"BlindSpotSupport", "HardwareDetected", "OpenpilotLongitudinal", "PedalSupport", "RadarSupport", "SDSUSupport", "SNGSupport"};

  QSet<QString> parentKeys;

  StarPilotSettingsWindow *parent;

  ParamControl *disableOpenpilotLong;
  ParamControl *forceFingerprint;

  Params params;
  Params params_memory{"", true};

  QMap<QString, QString> carModels;
};
