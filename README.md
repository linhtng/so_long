<h1 align="center">
	📖 So_long 
</h1>
<p align="center">
	<b><i>And thanks for all the keys!🔑</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/linhtng/so_long?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/linhtng/so_long?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/linhtng/so_long?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/linhtng/so_long?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/linhtng/so_long?color=green" />
</p>

---

## 💡 About the project
This project is a very small 2D game. Its purpose is to make you work with textures, sprites, and some other very basic gameplay elements.
In my case, the game is about a pink monster picking up all the keys to open the dungeon door and exit.

![](so_long_small_map_demo.gif)

### How to play
---
###### Maps
The game is able to play any map you want as long as it follow some specific rules:
* The map has to be a ``.ber`` file.
* It can only contain some of the following characters:

| Character | Object |
| - | - |
| 1 | Wall. |
| 0 | Empty space. |
| C | Collectable. |
| E | Exit. |
| P | Player starting position. |

* The map must be a rectangle surrounded by walls ‘1’.
* It must have at least one collectable ‘C’, and only one player ‘P’ and one exit 'E'.

See some examples in the ``maps`` folder of this project.

###### Controls
Use ``WASD`` to move. You can move in all directions but cannot move through the wall. After picking up all the keys, the door opens and you may leave. The shell will print how many moves you’ve used to solve the map on standard output.

You can close the game with ``esc`` or mouse click at 'X' button.

### Installation
---
#### Cloning the repositories
```shell
git clone https://github.com/linhtng/so_long
cd so_long
make
```
#### Usage
Passing the map you want to play as parameter (``./so_long map_file_input.ber``)

---
###### For more detailed information about the subject requirement, look at the [so_long.pdf](https://github.com/linhtng/so_long/files/11149130/so_long.pdf) and [so_long_eval_form.pdf](https://github.com/linhtng/so_long/files/11149132/so_long_eval_form.pdf)
