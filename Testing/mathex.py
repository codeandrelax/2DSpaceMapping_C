##
# @file mathex.py
#
# @brief Lidar data visualization and controlling a robot through a WebSocket connection
#
# @section description_sensors Description
# Defines the base and end user classes for various sensors.
# - Sensor (base class)
# - TempSensor
#
# @section libraries / modules
# - random standard library    (https://pypi.org/project/random/)
# - pygame standard library    (https://pypi.org/project/pygame/)
# - numpy standard library     (https://numpy.org)
# - time standard library      (https://docs.python.org/3/library/time.html)
# - math standard library      (https://math.org)
# 
# @section notes
# - Comments are Doxygen compatible.
#
# @section author
# - Created by 2D_SpaceMapping_C_group on 03/08/2024
#
import pygame
import math
import random
import time

pygame.init()

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (200, 200, 200)

# Button properties
BUTTON_WIDTH = 120
BUTTON_HEIGHT = 50
BUTTON_MARGIN = 20

LIDAR_RESOLUTION = 20

# Set up window
width, height = 600, 400
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Simulator")

# Fonts
font = pygame.font.SysFont(None, 40)

global start_button_rect, stop_button_rect

def GenerateLinePositions(numberOfLines):
    angle = 360/numberOfLines
    lines = []
    for x in range(numberOfLines):
        lines.append([300 * math.cos((x) * angle/180 * math.pi), 300 * math.sin((x) * angle / 180 * math.pi)])
    return lines

##
# function to draw buttons START and STOP
#
def draw_button(text, x, y, color):
    pygame.draw.rect(screen, color, (x, y, BUTTON_WIDTH, BUTTON_HEIGHT))
    text_surface = font.render(text, True, BLACK)
    text_rect = text_surface.get_rect(center=(x + BUTTON_WIDTH // 2, y + BUTTON_HEIGHT // 2))
    screen.blit(text_surface, text_rect)

##
# function to draw lines representing distance from obstancle to vehicle
#
def draw_lines(line_positions):
    for pos in line_positions:
        pygame.draw.line(screen, BLACK, (width // 2, height // 2), (width // 2 + pos[0], height // 2 + pos[1]), 1)

def GenerateRandomLinePositions(numberOfLines):
    lines = []
    for _ in range(numberOfLines):
        lines.append([random.uniform(-300, 300), random.uniform(-300, 300)])
    return lines
    
# line_positions = GenerateLinePositions(LIDAR_RESOLUTION)  

# random data to be visualized
line_positions = GenerateRandomLinePositions(LIDAR_RESOLUTION)

##
# main loop 
#
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            x, y = pygame.mouse.get_pos()
            if start_button_rect.collidepoint(x, y):
                print("Start button clicked")
            elif stop_button_rect.collidepoint(x, y):
                print("Stop button clicked")

    screen.fill(WHITE)

    line_positions = GenerateRandomLinePositions(LIDAR_RESOLUTION)
    time.sleep(1)  # Delay for 1 second

    # Draw lines
    draw_lines(line_positions)

    # Draw buttons
    draw_button("START", BUTTON_MARGIN, height // 2 - BUTTON_HEIGHT // 2, GRAY)
    draw_button("STOP", width - BUTTON_WIDTH - BUTTON_MARGIN, height // 2 - BUTTON_HEIGHT // 2, GRAY)

    # Get button rectangles for collision detection
    start_button_rect = pygame.Rect(BUTTON_MARGIN, height // 2 - BUTTON_HEIGHT // 2, BUTTON_WIDTH, BUTTON_HEIGHT)
    stop_button_rect  = pygame.Rect(width - BUTTON_WIDTH - BUTTON_MARGIN, height // 2 - BUTTON_HEIGHT // 2, BUTTON_WIDTH, BUTTON_HEIGHT)
    
    pygame.display.flip()

pygame.quit()

