from PIL import Image

im = Image.open('data/image.jpg') # Can be many different formats.
pix = im.load()
print(im.size)  # Get the width and hight of the image for iterating over


def bitfield(n):
    return [int(digit) for digit in bin(n)[2:]]


for y in range(im.size[1]):
    for x in range(im.size[0]):
        v = (pix[x,y][0]%2 << 7, pix[x,y][1]%2 << 7, pix[x,y][2]%2 << 7)
        # print(v)
        pix[x,y] = v

  # Set the RGBA Value of the image (tuple)
im.save('data/image2.jpg')  # Save the modified pixels as .png



# output = ""
# for y in range(im.size[1]):
#     for x in range(im.size[0]):
#         output += "".join(str(a) for a in bitfield(pix[x,y][0])[-1:])
#         output += "".join(str(a) for a in bitfield(pix[x,y][1])[-2:])
#         output += "".join(str(a) for a in bitfield(pix[x,y][2])[-2:])

# print(output)