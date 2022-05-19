from PIL import Image
image = Image.open('sprites/font.png')
width, height = image.size
pixels = image.load()
print(width,height)

# Check if has alpha, to avoid "too many values to unpack" error
has_alpha = len(pixels[0,0]) == 4

# Create empty 2D list
fill = 1
array = [[fill for x in range(width)] for y in range(height)]

for y in range(height):
    for x in range(width):
        if has_alpha:
            r, g, b, a = pixels[x,y]
            if a < 10:
                array[y][x] = [2,3,4]
            else:
                array[y][x] = [r/255,g/255,b/255]
        else:
            r, g, b = pixels[x,y]
            array[y][x] = [r/255,g/255,b/255] # Map values from range 0-255 to 0-1


file = open("l", "w+")
for x in array:
    e = ""
    for y in str(x):
        if y == "[":
            e = e + "{"
        elif y == "]":
           e = e + "}"
        else: e = e + y 
    file.write(str(e)+ '\n')
file.close()
