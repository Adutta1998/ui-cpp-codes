import raylib as rl
import math
from raylib import ffi

# Constants
WIDTH = 600
HEIGHT = 420
G = 10
MASS = 10

class Pendulum:
    def __init__(self, length, start, theta):
        self.length = length
        self.start = start # Expects a dict/struct with 'x' and 'y'
        self.theta = theta
        self.omega = 0.0  # angular velocity
        self.alpha = 0.0
        self.radius = 0.0  # angular acceleration
        # Calculate initial end point
        self.end = {
            "x": self.start["x"] + self.length * math.sin(self.theta),
            "y": self.start["y"] + self.length * math.cos(self.theta)
        }

    def display(self, mass=MASS):
        rl.DrawLine(int(self.start["x"]), int(self.start["y"]), 
                    int(self.end["x"]), int(self.end["y"]), rl.WHITE)
        self.radius = math.sqrt(mass / math.pi) * 5
        rl.DrawCircle(int(self.end["x"]), int(self.end["y"]), self.radius, rl.RED)

    def update(self, dt, damping, mass=MASS):
        # Angular acceleration: alpha = -(g/L) * sin(theta)
        self.alpha = -mass * (G / self.length) * math.sin(self.theta)
        self.radius = math.sqrt(mass / math.pi) * 5
        # Update velocity
        self.omega += self.alpha * dt
        self.omega *= damping

        # Update angle
        self.theta += self.omega * dt

        # Update end point
        self.end["x"] = self.start["x"] + self.length * math.sin(self.theta)
        self.end["y"] = self.start["y"] + self.length * math.cos(self.theta)

def main():
    rl.InitWindow(WIDTH, HEIGHT, b"pendulum")
    
    start_position = {"x": WIDTH / 2, "y": 30}
    # 90 * DEG2RAD is math.pi / 2
    pendulum = Pendulum(200, start_position, math.pi / 2)

    rl.SetTargetFPS(60)
    current_mass = ffi.new("float *", MASS)  # Create a mutable float pointer for the slider
    while not rl.WindowShouldClose():
        dt = rl.GetFrameTime()
        fps = rl.GetFPS()
        
        rl.BeginDrawing()
        rl.ClearBackground(rl.BLACK)
        
        pendulum.display(current_mass[0])
        pendulum.update(dt, 0.9995, current_mass[0])
        
        # Format string and convert to bytes for C-wrapper
        slider_rect = (150, 360, 300, 20)
        
        # GuiSlider modifies current_mass[0] in-place and returns an int (interaction status)
        rl.GuiSlider(slider_rect, b"Mass: 10", b"100", current_mass, 1.0, 200.0)
        status_text = f"FPS = {fps}, Mass = {current_mass[0]}".encode('utf-8')
        rl.DrawText(status_text, 250, 390, 10, rl.WHITE)
        rl.EndDrawing()

    rl.CloseWindow()

if __name__ == "__main__":
    main()