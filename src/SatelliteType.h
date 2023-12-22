//
// Created by wwwod on 17.11.2023.
//

#ifndef SATELLITESCHEDULE_SATELLITETYPE_H
#define SATELLITESCHEDULE_SATELLITETYPE_H

#define KINO_SPACE                  1000
#define ZORKIY_SPACE                500
#define SHOOTING_SPEED              0.5
#define KINO_TRANSMITTER_SPEED      0.125
#define ZORKIY_TRANSMITTER_SPEED    0.03125
#define OCCUPANCY_FOR_TRANSMITTING  0.298

enum class SatelliteType {
    KINO,
    ZORKIY
};

#endif //SATELLITESCHEDULE_SATELLITETYPE_H
