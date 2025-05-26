from pathlib import Path
import random
import csv

#test



def randomize(file_name):
    with open(file_name, "rt") as cf:
        reader = csv.reader(cf)
        vps_set = []
        for row in reader:
            vps_set.append(row)

    header = vps_set.pop(0)
    vps_set_shuffled = random.sample(vps_set, len(vps_set))

    out_file = file_name.parent / Path(file_name.stem + "_shuffled.csv")

    with open(out_file, "wt", newline="") as cf:
        csvwriter = csv.writer(cf)
        csvwriter.writerow(header)
        csvwriter.writerows(vps_set_shuffled)


if __name__ == "__main__":
    file_name = Path("./data/vps_set_4.csv")
    randomize(file_name)


