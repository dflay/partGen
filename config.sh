echo "Configuring partGen..."
cmake -DWITH_GEANT4_UIVIS=ON -DGeant4_DIR=/opt/local/lib/Geant4/Geant4.10.6/Geant4-10.6.0 \
      ../sources
echo "--> Done!"
echo "======================================================"
