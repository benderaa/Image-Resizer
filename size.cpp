#include <CImg.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

using namespace cimg_library;

bool check_divisible_by_2(int width, int height) {
    return (width % 2 == 0) && (height % 2 == 0);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: Accepts one image or folder as argument\n");
        return -1;
    }
    char* path = argv[1];
    struct stat s;
    if( stat(path,&s) == 0 )
    {
        // Ask the user if they want to convert the images to .img format
        int choice;
        printf("Do you want to convert the images to .img format? (1 for yes, 0 for no) ");
        scanf("%d", &choice);
        if( s.st_mode & S_IFDIR )
        {
            // it's a directory
            // Walk through all files in the folder
            DIR *d;
            struct dirent *dir;
            d = opendir(path);
            if (d) {
                while ((dir = readdir(d)) != NULL) {
                    if (!strcmp (dir->d_name, "."))
                        continue;
                    if (!strcmp (dir->d_name, ".."))
                        continue;
                    // Open the image file
                    char image_path[1024];
                    sprintf(image_path, "%s/%s", path, dir->d_name);
                    CImg<unsigned char> img(image_path);
                    // Get the dimensions of the image
                    int width = img.width();
                    int height = img.height();
                    float aspectRatio = (float) width / (float) height;
                    //Ask the user for the scaling factor
                    int x_factor;
                    printf("Enter x scaling factor: ");
                    scanf("%d", &x_factor);
                    //Calculate the new height based on the x factor and the aspect ratio
                    int new_height = (float)x_factor / aspectRatio;
                    // Resize the image with the aspect ratio preserved
                    img.resize(x_factor, new_height, -100, -100, 5);
                    // Check if the new width and height are divisible by 2
                    if (!check_divisible_by_2(img.width(), img.height())) {
                        printf("Error: new width and height are not divisible by 2\n");
                        continue;
                    }
                    // Save the resized image
                    char outpath[1024];
                    if (choice) {
                        // Convert the file extension to .img
                        char *dot = strr
                      sprintf(outpath, "resized_%s.img", dot);
                    } else {
                        sprintf(outpath, "resized_%s", dir->d_name);
                    }
                    img.save(outpath);
                }
                closedir(d);
            }
        }
        else if( s.st_mode & S_IFREG )
        {
            // it's a file
            CImg<unsigned char> img(path);
            // Get the dimensions of the image
            int width = img.width();
            int height = img.height();
            float aspectRatio = (float) width / (float) height;
            //Ask the user for the scaling factor
            int x_factor;
            printf("Enter x scaling factor: ");
            scanf("%d", &x_factor);
            //Calculate the new height based on the x factor and the aspect ratio
            int new_height = (float)x_factor / aspectRatio;
            // Resize the image with the aspect ratio preserved
            img.resize(x_factor, new_height, -100, -100, 5);
            // Check if the new width and height are divisible by 2
            if (!check_divisible_by_2(img.width(), img.height())) {
                printf("Error: new width and height are not divisible by 2\n");
                return -1;
            }
            // Save the resized image
            char outpath[1024];
            if (choice) {
                // Convert the file extension to .img
                char *dot = strrchr(path, '.');
                int dot_idx = dot - path;
                path[dot_idx] = '\0';
                sprintf(outpath, "%s.img", path);
            } else {
                sprintf(outpath, "resized_%s", path);
            }
            img.save(outpath);
        }
    }
    return 0;
}
