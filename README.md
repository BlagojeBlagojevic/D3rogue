# D3rogue
Game like rogue


<img width="1128" height="766" alt="Screenshot from 2025-09-30 15-02-59" src="https://github.com/user-attachments/assets/ae2f7ca3-40b4-49c1-a7de-57a9b14e238b" />
<img width="1200" height="700" alt="screenshot002" src="https://github.com/user-attachments/assets/83615348-b7d6-4a9a-900f-c9457a741f8b" />




# Game Controls Guide

## Overview
This is a turn-based game where you control a character in either 3D or 2D view. The game uses a grid-based movement system where each key press represents one turn.

## View Modes

### Switching Between Views
- **TAB** - Toggle between 3D and 2D view modes

## Movement Controls

### 3D Mode Movement
- **W** - Move forward (in the direction you're facing)
- **S** - Move backward (away from the direction you're facing)
- **Q** - Rotate 90 degrees counterclockwise
- **E** - Rotate 90 degrees clockwise
- **SPACE** - Wait/Skip turn (consumes gas)

### 2D Mode Movement
- **Arrow Keys** - Move in four directions (Up, Down, Left, Right)
- **SPACE** - Wait/Skip turn (consumes gas)

*Note: In 2D mode with 8-direction movement enabled, you may have additional diagonal movement keys.*

## Combat & Actions

### Attacking
- **Automatic** - When you try to move into an enemy's space, you will automatically attack instead

### Ranged Attacks
- **A** - Fire a ranged weapon (requires equipped bow and matching ammunition)

### Battle system 
The combat system is a multi-layered simulation that begins with a constitution check, where both attacker and defender roll against their constitution stats—if the attacker rolls higher, the defender immediately loses vitality equal to the difference. Attack resolution then proceeds through several stages: the attacker rolls a strength-based attack die while the defender attempts to dodge with a dexterity-based roll; both parties' equipped items add flat bonuses and special effects like critical strikes, lifesteal, bash stuns, thorns, and extra dodge chance, though equipment with strength requirements carries a risk of failure if the wielder lacks sufficient strength. If either combatant's vitality is depleted, their offensive or defensive capabilities are halved. Finally, if the attacker's roll exceeds the defender's dodge, damage is calculated by subtracting the defender's total armor from the attacker's total damage output, with the result clamped to a minimum of zero.



## Inventory & Items

### Inventory Management
- **I** - Toggle inventory screen
- **P** - Pick up items from the ground (opens pickup menu)
- **H** - Toggle character stats display

### Equipment
- You need both a ranged weapon and matching ammunition to use ranged attacks
- Different weapon types require specific ammunition types

## Game States & Effects

### Status Effects
- **Confusion** - When confused, your movements become random for a number of turns
- **Stun** - When stunned, you cannot move normally and may attack randomly when attempting to move
- Status messages will inform you of remaining turns for these effects


## Interface

### Additional Displays
- **M** - Toggle map display
- Various UI elements show your health, status effects, and available actions

## Game Flow
- Each key press typically advances one turn
- Enemies will take their turns after you complete your action
- Gas consumption occurs with most actions
- The game world updates after each turn

## Tips
- Plan your movements carefully as each action costs a turn
- Check your inventory regularly to ensure you have proper equipment
- Pay attention to status effect messages to understand combat limitations
- Use the wait action (SPACE) strategically when you need to conserve position

