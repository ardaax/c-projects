# A DIGITAL IMAGE CROPPING TOOL
>program.exe <InputImageFileName> <OutputCropImageFileName> <CropC> <CropR> <CropWidth> <CropHeight>

<InputImageFileName> : The input image file name which is a binary file in the given .IMG file
format explained under Section - BACKGROUND INFORMATION
<OutputCropImageFileName> : The output file name which the cropped region image data
will be written into. The file format will comply with the .IMG file format explained under
Section - BACKGROUND INFORMATION
<CropC> <CropR> <CropWidth> <CropHeight> : These four arguments describe the
rectangular cropping image coordinates and the width – height of the rectangular region.
For example; the below given figure depicts the meaning of CropC, CropR, CropWidth and
CropHeight values that determine the cropping rectangular region for the sample execution
with the below arguments:
hw3sol.exe applesRGB.IMG Out2.IMG 151 83 100 100

Our .IMG files are composed of a simple file header of size 14 bytes that contains information about the
image properties, followed by the image pixel data array.

