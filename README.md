# Unreal Engine 5 Game AI

NPC AI for Unreal Engine 5 written in **C++**, built on the engine's Behavior Tree, Blackboard, and Navigation systems. I used this project to learn how Unreal's AI framework fits together below the Blueprint layer.

## Features
- **Custom AI Controller** (`ANPC_AIController`): when it possesses an NPC, it binds the NPC's Blackboard and starts its Behavior Tree.
- **NPC character** (`ANPC`): each NPC exposes its own `UBehaviorTree` in the editor, so different NPCs can run different behaviors.
- **Custom Behavior Tree tasks in C++**
  - `Find Random Location in NavMesh`: picks a random reachable point within a configurable radius, used for patrolling.
  - `Find Player Location`: targets the player directly, or a random reachable point near them, used for chasing and searching.

## How it works
```
NPC (ACharacter) ──possessed by──► NPC_AIController
                                     │ UseBlackboard() + RunBehaviorTree()
                                     ▼
                              Behavior Tree
                     ┌───────────────┴───────────────┐
           Find Player Location            Find Random Location
     (UNavigationSystemV1 → Blackboard)  (UNavigationSystemV1 → Blackboard)
                                     ▼
                                 Move To
```

## Source layout
| File | Purpose |
|---|---|
| `Source/AIDeneme/NPC.*` | NPC character that exposes its Behavior Tree |
| `Source/AIDeneme/NPC_AIController.*` | Sets up the Blackboard and runs the tree on possession |
| `Source/AIDeneme/MyBTTask_FindRandomLocation.*` | Patrol task: random point on the NavMesh |
| `Source/AIDeneme/BTTask_FindPlayerLocation.*` | Chase/search task targeting the player |

## Running it
1. Install **Unreal Engine 5** and Visual Studio with the "Game development with C++" workload.
2. Clone the repo, right-click `AIDeneme2.uproject`, and choose **Generate Visual Studio project files**.
3. Open the `.uproject`, let the editor compile the module, and press **Play**.
