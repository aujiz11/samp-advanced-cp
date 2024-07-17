# SAMP Advanced Checkpoint

## Table of Contents

* [Introduction](#introduction)
* [Installation](#Installation)
* [Testing](#testing)
* [Usage](#usage)

## Introduction

The SetPlayerCheckpoint function only provides one checkpoint for the player, then one day I needed something that could manipulate and create multiple checkpoints at the same time so I created this library.

## Installation

Simply install to your project:

```bash
sampctl package install aujiz11/samp-advanced-cp
```

Include in your code and begin using the library:

```pawn
#include <advanced_cp>
```

## Testing

<!--
	Depending on whether your package is tested via in-game "demo tests" or
	y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl package run
```

## Usage

**Functions**
```
Function:
	CreateAdvancedCP

Info:
	Creates advanced checkpoints for players, previously created points will not be lost unless you do not use DestroyAdvancedCP

Params:
    * playerid -> Player ID
    * Float:centreX -> X coordinate of checkpoint
    * Float:centreY -> Y coordinate of checkpoint
    * Float:centreZ -> Z coordinate of checkpoint
    * Float:size -> Checkpoint size

Return:
    Returns checkpoint id, -1 if failed (player checkpoint ID starts at 0)

____________________________________________________________

Function:
	DestroyAdvancedCP

Info:
	Remove advanced checkpoint

Params:
    * playerid -> Player ID
    * checkpointid -> Checkpoint ID to delete (ADVANCEDCP_UKNOWN to delete all of the player)

Return:
    Returns true if the execution is successful, false if it fails

____________________________________________________________

Function:
	IsPlayerInAdvancedCP

Info:
	Check which players are inside the advanced 
    
Params:
    * playerid -> Player ID
    * checkpointid -> Checkpoint ID to check

Return:
    Returns true if the player is inside, returns false if the player is not inside

____________________________________________________________

Function:
	GetPlayerAdvancedCP

Info:
	Check which players are inside the advanced 
    
Params:
    * playerid -> Player ID
    * checkpointid -> Checkpoint ID to check
    * &Float:centreX -> Get the X coordinate value
    * &Float:centreY -> Get the Y coordinate value
    * &Float:centreZ -> Get the Z coordinate value

Return:
    Returns true if the execution is successful, false if it fails
```

**Callbacks**
```
// called when the player steps on the advanced checkpoint
forward OnPlayerEnterAdvancedCP(playerid, checkpointid);
```