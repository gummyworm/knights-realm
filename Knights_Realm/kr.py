import engine

def onCollide(e):
		print("collision")
		return
g = engine.Game()

"""
tnode = engine.Node(10, 10, 30, 0)
ts = engine.Sprite("testsprite.spr")
tnode.AddChild(ts)
g.AddEntity(tnode)
tnode.SetX(250)
"""

g.Setup()
#g.Accept("two-into-one", tnode, onCollide)
#g.Accept("one-into-two", tnode, onCollide)

g.Run()