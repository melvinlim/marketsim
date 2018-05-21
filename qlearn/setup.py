from distutils.core import setup, Extension

module1 = Extension('qlearn',
                    sources = ['main.cpp','gamecontroller.cpp','player.cpp','world.cpp','object.cpp','qfunction.cpp','mynn/layer.cpp','mynn/net.cpp','mynn/data.cpp','mynn/idx.cpp','mynn/mnist.cpp','mynn/xor.cpp'])

setup (name = 'QLearn',
       version = '1.0',
       description = 'Q Learning package',
       ext_modules = [module1])
