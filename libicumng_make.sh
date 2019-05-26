########################################################################
#Configuramos el entorno VisualCobol Development Hub para              #
#sobreescribirlo sobre el de VisualCobol Server                        #
########################################################################
. /swmango/visualcobol/bin/cobsetenv /swmango/visualcobol
. /swmango/scripts/EXPL/cobsetenvMNG

# Build executable
#echo Building executable...
#cob -CC -I/usr/icu4c/include -CC -bnoquiet wrapper.cpp Translitera.cpp unaccent.cpp util.cpp -o testLibICU -L/usr/icu4c/lib -licuuc -licui18n
#cob -CC -CC -bnoquiet libmng.cpp
#rm -f libicumng.o

# Build shared libary
echo "\n*****Building shared libary..."
cob -zv -CC -bnoquiet libicumng.cpp unaccent.cpp util.cpp -L/usr/icu4c/lib  -o libicumng.so -licuuc -licui18n -e ""
if [ $? != 0 ]; then
   echo "\n*****ERROR Building shared libary."
   exit;
fi
rm -f libicumng.o
#cp libicumng.so libicumng.so

#echo "\n*****Dumping Shared Library..."
#nm -X64 libicumng.so |grep -e ^mng*\(* -e ^cls*

echo "\n*****Deleting Shared Library..."
rm -f /MNG/DESA/VOBJ/libicumng.so
ssh -i /MNG/DESA/.ssh/id_rsa desa@parmenides -o UserKnownHostsFile=/home/keys/known_hosts  "rm -f $VOL/DESA/VOBJ/libicumng.so"
echo "\n*****Copying Shared Library..."
cp -p libicumng.so /MNG/DESA/VOBJ
scp  -q -i /home/keys/id_rsa -o UserKnownHostsFile=/home/keys/known_hosts libicumng.so desa@parmenides:$VOL/DESA/VOBJ/libicumng.so

typeset -u REPLY
until [[ $REPLY = "S" ]] || [[ $REPLY = "N" ]]
do
    printf '\nSubir libreria a produccion? [S/N]: '
    read
done
if [[ $REPLY = "S" ]]
then
    RCEXPL BASE0113 'ssh -i /MNG/DESA/.ssh/id_rsa -o UserKnownHostsFile=/home/keys/known_hosts rootexp@zenon "rm -f /MNG/EXPL/VOBJ/libicumng.so"'
    RCEXPL BASE0113 "scp -q -i /home/keys/id_rsa -o UserKnownHostsFile=/home/keys/known_hosts /MNG/DESA/VOBJ/libicumng.so rootexp@zenon:/MNG/EXPL/VOBJ/libicumng.so"
    echo "\n***Subida a produccion realizada***\n"
    #$*
fi