
from distutils.core import setup, Extension
import glob

MainSrc= glob.glob('*.cpp')
TiXMLSrc = glob.glob('tinyxml/*.cpp')

LIBS = ['mingw32', 'SDLmain', 'SDL', 'SDL_image', 'opengl32']
SRC = MainSrc + TiXMLSrc

engine_module = Extension('_engine',
        sources=SRC,
        libraries=LIBS,
        )

setup(name = 'engine',
        version = '0.1',
        author = "Bryce Wilson",
        description = """Knights Realm Engine""",
        ext_modules = [engine_module],
        py_modules = ["engine"],
        )
