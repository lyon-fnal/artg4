# Build the libraries
art_make(SERVICE_LIBRARIES 
"artg4_actionBase" 
"artg4_util" 
"${XERCESCLIB}" 
"${G4_LIB_LIST}")

# Copy the headers
install_headers()
