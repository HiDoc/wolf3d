name=$1

if [ $# -eq 0 ]
then
	echo "Usage: sh sync.sh [doom_nukem path]"
	exit 0
fi

cp -r $name/rsrc/sound/ambiance ressources/
cp -r $name/rsrc/skybox ressources/
cp -r $name/rsrc/img/ceil ressources/images/
cp -r $name/rsrc/img/floors ressources/images/
cp -r $name/rsrc/img/consumable ressources/objects/
cp -r $name/rsrc/img/enemies ressources/objects/
cp -r $name/rsrc/img/posters ressources/objects/
cp -r $name/rsrc/img/walls ressources/images/
