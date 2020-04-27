//
// Created by Denys Kotelovych on 07.09.18.
//

#ifndef RVIZ_VIVE_PLUGIN_VIVE_CONVERSIONS_H
#define RVIZ_VIVE_PLUGIN_VIVE_CONVERSIONS_H

#include <Qt3DCore/Qt3DCore>
#include "vive.hh"


struct Pose {
  QVector3D Position;
  QQuaternion Orientation;
};

struct Controller {
    struct Pose Pose;
    QVector3D TrackpadPosition;
    bool TriggerPressed;
    bool TrackpadPressed;
    bool MenuPressed;
    bool GripPressed;
};

struct HMD {
    struct Pose Pose;
};

QVector3D TranslatePositionToOgreCoordinateSystem(const QVector3D &position);

QQuaternion TranslateOrientationToOgreCoordinateSystem(const QQuaternion &orientation);

QMatrix4x4 Convert(const vr::HmdMatrix34_t &matPose);

QMatrix4x4 Convert(const vr::HmdMatrix44_t &matPose);

Pose Convert(const vr::TrackedDevicePose_t &pose);

HMD Convert(const Vive::HMD &hmd);

Controller Convert(const Vive::Controller &controller);


#endif //RVIZ_VIVE_PLUGIN_CONVERT_VIVE_H
