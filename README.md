# SaveLoadSample

This is a demo unreal engine 5.1 project of a load and save mechanism using binary serialization to save game data. Focus on Blueprint Usage

## How To Use It

- Mark your Actor with ISavable intefaces
- Mark you UPROPERTY with SaveGame flag
- Add to you actor SaveLoadComponent
- Link it together (Bluprint or C++ class does not metter)
- Call SaveGameToSlot and LoadGameToSlot function from DemoGameState
- Enjoy

## Save and Load in Runtime Mode
![](https://github.com/Antonbreakble/SaveLoadSample/blob/main/AdditionalContent/runtime.gif)

## Load From Slot After Restart Game
![](https://github.com/Antonbreakble/SaveLoadSample/blob/main/AdditionalContent/restart.gif)
