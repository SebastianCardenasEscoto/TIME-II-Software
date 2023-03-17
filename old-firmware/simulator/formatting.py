from tkinter import *
import os
from PIL import Image, ImageTk



# Colors
darkish = '#%02x%02x%02x' % (29, 30, 38)
whitish = '#%02x%02x%02x' % (214, 216, 218)
code_green = '#%02x%02x%02x' % (80, 200, 70)
code_green_light = '#%02x%02x%02x' % (170, 200, 150)
code_dark = '#%02x%02x%02x' % (23, 24, 30)

root = Tk()
root.configure(bg=darkish)

root.title("Time II Flight Simulator")

# display everything
top = root.winfo_toplevel()
menuBar = Menu(top)
top['menu'] = menuBar
subMenu = Menu(menuBar)
portMenu = Menu(menuBar)

w = Label(root, text="Time II Flight Simulator", font='Helvetica 20 bold', bg=darkish, fg=whitish).grid(row=0, column=0, columnspan=6, padx=10)

text_packet = Label(text="", bg=darkish, fg=whitish).grid(row=18, column=0)

# Style
s = ttk.Style()
s.theme_use('clam')
s.configure("green.Horizontal.TProgressbar",  troughcolor=code_dark, bordercolor=code_dark, background=code_green, lightcolor=code_green, darkcolor=code_dark)

progress = ttk.Progressbar(root, style="green.Horizontal.TProgressbar", orient=HORIZONTAL, length=600, mode='determinate')
progress.grid(row=8, column=0)
#progress.start()


packet_title = Label(text="Text Packet:", font ='Helvetica 18 bold', bg=darkish, fg=whitish).grid(row=11, column=0)
restart = Button(root, text="Restart", font='Helvetica 15 bold', bg=darkish, highlightbackground=darkish, highlightthickness=30, foreground=whitish).grid(row=0, column=3)

hardwareOutput = Label(text="Microprocessor Output   \n", font='Helvetica 18 bold', bg=darkish, fg=whitish).grid(row=19, column=0)

#logo
scale = 3
logo_path = os.path.join(os.getcwd(), 'logo.png')
logo = ImageTk.PhotoImage(Image.open(logo_path).resize((scale*53,scale*19), Image.ANTIALIAS))
imgLabel = Label(root,image=logo)
imgLabel.grid(row=0, column=0)



