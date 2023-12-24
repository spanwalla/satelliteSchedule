import re
from datetime import datetime


def detect_satellite(index: int) -> tuple:
    if 110101 <= index <= 110510:
        return 1000, 0.5, 0.125,  # Киноспутник: объём памяти, скорость съёмки, скорость передачи
    elif 110601 <= index <= 112010:
        return 500, 0.5, 0.03125,  # Зоркий: объём памяти, скорость съёмки, скорость передачи
    else:
        raise KeyError(f"Wrong satellite index: {index}.")


def to_transmit(current_memory: int, interval: tuple, transmitter_speed: int) -> int:
    can_transmit = transmitter_speed * (interval[1] - interval[0]).total_seconds()
    if current_memory < can_transmit:
        can_transmit = current_memory
    return can_transmit


def to_shoot(current_memory: int, space: int, interval: tuple, shooting_speed: int) -> int:
    shot = shooting_speed * (interval[1] - interval[0]).total_seconds()
    if current_memory + shot > space:
        shot = space - current_memory
    return shot


def validator(path: str):
    f = open(path, 'r')
    satellites = dict()
    stations = dict.fromkeys(['Norilsk', 'Anadyr2', 'Irkutsk', 'Murmansk1', 'Anadyr1', 'Sumatra', 'RioGallegos',
                              'Magadan1', 'Magadan2', 'Murmansk2', 'Novosib', 'Moscow', 'CapeTown', 'Delhi'], 0)
    shooting_satellites = []
    transfers = []
    current_str = 1
    current_interval = (None, None)
    for line in f:
        j = re.match(r"^\[(.+), (.+)]$", line)
        if j is not None:
            if len(shooting_satellites) > 0 or len(transfers) > 0:
                transferred = []
                for transfer in transfers:
                    if transfer[1] in shooting_satellites:
                        raise RuntimeError(f"Line: {current_str}. Interval: [{current_interval[0]}, {current_interval[1]}]. SATELLITE TRANSFER&SHOOTING.")
                    if transfer[0] in transferred:
                        raise RuntimeError(f"Line: {current_str}. Interval: [{current_interval[0]}, {current_interval[1]}]. STATION DUPLICATE TRANSFERRING.")

                    if transfer[1] not in satellites:
                        satellites[transfer[1]] = 0
                    if satellites[transfer[1]] <= 0:
                        raise RuntimeError(f"Line: {current_str}. Interval: [{current_interval[0]}, {current_interval[1]}]. TRANSFER FROM EMPTY SATELLITE.")

                    satellite_parameters = detect_satellite(int(transfer[1]))

                    mem = to_transmit(satellites[transfer[1]], current_interval, satellite_parameters[2])
                    satellites[transfer[1]] -= mem
                    stations[transfer[0]] += mem
                    transferred.append(transfer[0])

                for shooting in shooting_satellites:
                    if shooting not in satellites:
                        satellites[shooting] = 0
                    if shooting in [k[1] for k in transfers]:
                        raise RuntimeError(f"Line: {current_str}. Interval: [{current_interval[0]}, {current_interval[1]}]. SATELLITE TRANSFER&SHOOTING.")
                    satellite_parameters = detect_satellite(int(shooting))
                    if satellites[shooting] >= satellite_parameters[0]:
                        raise RuntimeError(f"Line: {current_str}. Interval: [{current_interval[0]}, {current_interval[1]}]. SATELLITE {shooting} MEMORY OVERFLOW.")
                    satellites[shooting] += to_shoot(satellites[shooting], satellite_parameters[0], current_interval, satellite_parameters[1])

            shooting_satellites.clear()
            transfers.clear()
            current_interval = (datetime.fromisoformat(j[1]), datetime.fromisoformat(j[2]))

        else:
            j = re.match(r"^Satellite-KinoSat_(\d{6})$", line) # shooting
            if j is not None:
                shooting_satellites.append(j[1])
            else:
                j = re.match(r"^(.+):Satellite-KinoSat_(\d{6})$", line) # transmitting
                if j is not None:
                    transfers.append([j[1], j[2]])
        current_str += 1

    f.close()
    print(stations, sum(stations.values()))
    for k in satellites.items():
        print(k[0], round(k[1], 2))


if __name__ == "__main__":
    try:
        validator('build/result.txt')
        print("Validation passed.")
    except RuntimeError as e:
        print(e)
