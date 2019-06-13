local factory = game.GOFactory()

local ship1 = factory.Create(1)
               .Position(3, 4)
               .Speed(0, 30)
               .Rotation(90)
               .Body({
                  {0, 3},
                  {1, 2},
                  {0.6, -1.5},
                  {-0.6, -1.5},
                  {-1, 2}
               }, Color("red"))

local cannon1 = factory.Create()
                  .Position(0, 0)
                  .RelativePosition(0, 0)
                  .Rotation(90)
                  .Body({
                     -- etc.
                  }, Color("yellow"))
                  .Weapon(CannonWeapon({range = 75, rof = 1, speed = 100}))
ship1.Container({cannon1})

-- "game" will be a global table: {GOFactory = C++ function proxy which returns a full userdata proxy to the GameObjectFactory singleton}
-- Later on, we will improve this metatable to support configuration options read from a conf.lua file. These options will be represented as keys in the index table that will be implemented in C++ as functions which set the corresponding values on the Game singleton object

-- the factory userdata proxy will