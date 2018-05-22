from distutils.core import setup, Extension

module1 = Extension('qlearn',
                    sources = ['main.cpp','player.cpp','qfunction.cpp','mynn/layer.cpp','mynn/net.cpp','mynn/idx.cpp'])

setup (name = 'QLearn',
       version = '1.0',
       description = 'Q Learning package',
       ext_modules = [module1])
