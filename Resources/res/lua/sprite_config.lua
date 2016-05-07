-- this lua file contains information on the spritesheets to import. It will be used by TextureManager. 
-- This is a module. import to other lua file using require "sprite_config"
sprite_config={}
sprite_config["path"]="Assets/spritesheet/"
sprite_config["types"]={"basic_zombie","swiss","chucker","healer", "spit","effects"}
sprite_config["total"]=6 --total number of sprite types.
sprite_config["plist_ending"]="_sprites.plist"
sprite_config["png_ending"]="_sprites.png"
sprite_config["next_file"]=function(index)
    return {sprite_config["path"]..sprite_config["types"][index+1].."/"..sprite_config["types"][index+1]..sprite_config["plist_ending"],
    sprite_config["path"]..sprite_config["types"][index+1].."/"..sprite_config["types"][index+1]..sprite_config["png_ending"]}
  end

