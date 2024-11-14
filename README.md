Sparty's Boots Project
Sparty's Boots is an interactive C++ game that integrates the simulation of logic circuits with entertaining animations. The project will simulate a sorting system using a conveyor belt on which its main character, Sparty, kicks products off, depending on pre-programmed logics through logic gates and sensor inputs.

Features
Logic Gate Simulation: AND, OR, NOT, and flip-flop driving Sparty to kick, hence imitating a simple logic circuit.

Dynamic Product Sorting: The products will travel along a conveyor belt and will be sorted out based on conditions given by logic gates and sensors.
Object-Oriented Design: Applies inheritance and polymorphism to implement the various game entities (like conveyor, gates, sensors, and products) in a modular way.
Event-Driven Interaction: Sparty is kicking items off the conveyor in reaction to sensor inputs and circuit evaluations, prompting immediate action from the player.
Multi-level support: the game will support several levels, with different conditions for Sparty acting-this should make it progressively harder.

Technologies
Language: C++
Framework: wxWidgets (for GUI, animations, and user interaction).
Design Patterns: Visitor pattern for item interactions, and observer pattern for real-time updates in-game.

How It Works
It contains a conveyor belt with products and sensors positioned along the path. Logic gates in the construction of a circuit allow specifying under which conditions Sparty should kick a product. The output of each sensor turns on the circuit connected with it as every product hits it, and thus automatically triggers Sparty to kick if conditions are met. There are higher levels of difficulty that can be advanced with logic.
