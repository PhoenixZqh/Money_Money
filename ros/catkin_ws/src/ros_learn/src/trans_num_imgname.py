import os
import re


def rename_images_to_numbers(folder_path):
    image_files = [
        f for f in os.listdir(folder_path)
        if os.path.isfile(os.path.join(folder_path, f))
    ]

    # Sort the image files to ensure they are processed in order
    image_files.sort()

    for i, filename in enumerate(image_files, start=1):
        # Extract the numeric part from the filename using regular expression
        match = re.search(r'\d+', filename)
        if match:
            numeric_part = match.group()
            new_filename = str(i) + '.jpg'
            os.rename(os.path.join(folder_path, filename),
                      os.path.join(folder_path, new_filename))
            print(f"Renamed {filename} to {new_filename}")


# Replace 'your_folder_path' with the path to the folder containing the images
folder_path = '/home/zqh/DATA/pic'
rename_images_to_numbers(folder_path)
