import os
genv=DefaultEnvironment()
build_path="build"
os.system("mkdir -p "+ build_path)
genv["ENV"]["PATH"]+= ":/home/kzawisto/Projects/CMS/root/bin"
genv["CXXFLAGS"]="-std=c++11"
genv.Append(CPPPATH=["#DataIO/include","#HistogramGui/include"])
genv.Append(LIBPATH="#build")
Export("genv")
shared=SConscript("DataIO/SConscript",variant_dir="build/DataIO_build",duplicate=0)
exec1=SConscript("HistogramGui/SConscript",variant_dir="build/HistoGui_build",duplicate=0)
Depends(exec1,shared)
os.system("cp DataIO/config.json build")
os.system("cp DataIO/TestData.root build")
