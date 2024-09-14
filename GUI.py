import tkinter as tk
from PIL import ImageTk,Image

import speech_recognition as sr
import pyttsx3
import serial
import time
import socket

esp_ip = "172.20.10.9"
esp_port = 80

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((esp_ip, esp_port))

def send(message):
    try:
        sock.sendall(message.encode() + b'\n')
    except KeyboardInterrupt:
        print("Closing connection")
    finally:
        pass

recognizer = sr.Recognizer()
engine = pyttsx3.init()
def speak(text):
    engine.say(text)
    engine.runAndWait()

#ser = serial.Serial('COM3', 9600)


def listen_for_commands(c):
    global Flag

    #with sr.Microphone() as source:
        #print("Listening for commands...")
        #audio = recognizer.listen(source)
    try:
            #command = recognizer.recognize_google(audio).lower()
        print(f"Command recognized: {c}")
        if "forward" in c:
                #ser.write(b'F')
            print('Forward')
            send('w')
            
        elif "backward" in c:
                #ser.write(b'B')
            print('Backward')
            send('d')

        elif "left" in c:
                #ser.write(b'L')
            print('Left')
            send('a')

        elif "right" in c:
                #ser.write(b'R')
            print('Right')
            send('d')

        elif "stop" in c:
            print ('Stop')
            send('s')

        elif "off" in c:
            print ('Deactivate')            
            Flag=False
        else:
            #ser.write(b'S')  # Stop or no action
            print('Stop')
    except sr.UnknownValueError:
        print("Sorry, I did not understand the audio.")
    except sr.RequestError:
        print("Sorry, there was an error with the speech recognition service.")


def StartVoice():
    
    global Flag
    Flag=True
    while Flag:
        r = sr.Recognizer()
        try:
            with sr.Microphone() as source:
                print("Salmon Boi Activated....")
                audio = r.listen(source)
                command = r.recognize_google(audio)

                listen_for_commands(command)

        except Exception as e:
            print("Error; {0}".format(e))

def on_click(event):
    item = canvas.find_withtag("current")[0]
    
    if item == Up:
        print("Up")
        send('f')
    elif item == Down:
        print("Down")
        send('b')
    elif item == Left:
        print("Left")
        send('l')
    elif item == Right:
        print("Right")
        send('r')
    elif item == Voice:
        print('Voice')
        StartVoice()
    elif item == Stop:
        print('Stop')
        send('s')


        
root = tk.Tk()
canvas = tk.Canvas(root, width=600, height=500, bg='white')
canvas.pack()

bg=Image.open('im.png')
rebg=bg.resize((600,500),Image.LANCZOS)
i=ImageTk.PhotoImage(rebg)
canvas.create_image(0,0,image=i,anchor='nw')

canvas.create_text(300, 30, text = "VoBOT", font = ("Arial", 30),fill='white')
Up = canvas.create_polygon(300, 100, 250, 200, 350, 200, fill='red',width=10)
Down = canvas.create_polygon(250, 370, 300, 470, 350, 370, fill='red')
Left = canvas.create_polygon(200, 335, 100, 285, 200, 235, fill='red')
Right = canvas.create_polygon(400, 235, 400, 335, 500, 285, fill='red')
Voice = canvas.create_oval(350, 235, 250, 335,fill='yellow')
canvas.create_text(300, 285, text = "Voice", font = ("Arial", 15))
Stop = canvas.create_oval(10, 490, 110, 390,fill='pink')
canvas.create_text(60, 440, text = "Stop", font = ("Arial", 15))


canvas.tag_bind(Up, '<ButtonPress-1>', on_click)
canvas.tag_bind(Down, '<ButtonPress-1>', on_click)
canvas.tag_bind(Left, '<ButtonPress-1>', on_click)
canvas.tag_bind(Right, '<ButtonPress-1>', on_click)
canvas.tag_bind(Voice, '<ButtonPress-1>', on_click)
canvas.tag_bind(Stop, '<ButtonPress-1>', on_click)




root.mainloop()

