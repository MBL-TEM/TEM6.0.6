CXX = g++
CFLAGS = -O2

CLMOBJ = tclm606b.o  

LULCOBJ = tbiome606.o tlcluc606.o

TEMOBJ = ttem606c.o atms606b.o tveg606c.o tmcrb606b.o \
tsoil606b.o qsoiltemp606b.o  humnact606c.o

TEMACTOBJ = ttem606cConstActLayer.o atms606b.o tveg606c.o tmcrb606b.o \
tsoil606bConstActLayer.o qsoiltemp606b.o  humnact606c.o

TEMNOFERTOBJ = ttem606cNoFert.o atms606b.o tveg606cNoFert.o tmcrb606b.o \
tsoil606b.o qsoiltemp606b.o  humnact606cNoFert.o

TEMNOFERT2000OBJ = ttem606cNoFert2000.o atms606b.o tveg606cNoFert2000.o tmcrb606b.o \
tsoil606b.o qsoiltemp606b.o  humnact606cNoFert2000.o

ELMNTOBJ = elmnt605.o telm606c.o latdat602.o \
tclmdat606.o tco2dat437.o tndepdat605.o \
lulcdat605.o tmaxcohortdat605.o \
ttemdat606.o telvdat605.o tsoldat606.o 

ELMNTACTOBJ = elmnt605.o telm606cConstActLayer.o latdat602.o \
tclmdat606.o tco2dat437.o tndepdat605.o \
lulcdat605.o tmaxcohortdat605.o \
ttemdat606.o telvdat605.o tsoldat606.o

ELMNTNOFERTOBJ = elmnt605.o telm606cNoFert.o latdat602.o \
tclmdat606.o tco2dat437.o tndepdat605.o \
lulcdat605.o tmaxcohortdat605.o \
ttemdat606.o telvdat605.o tsoldat606.o

ELMNTNOFERT2000OBJ = elmnt605.o telm606cNoFert2000.o latdat602.o \
tclmdat606.o tco2dat437.o tndepdat605.o \
lulcdat605.o tmaxcohortdat605.o \
ttemdat606.o telvdat605.o tsoldat606.o

ELMNTOBJA = elmnt605.o telm606b.o latdat602.o \
tclmdat606.o tco2dat437.o tndepdat605.o \
lulcdat605.o tmaxcohortdat605.o \
ttemdat606.o telvdat605.o tsoldat605.o 

OBJ =  tprocessXML606.o

xtem606c : ${CLMOBJ} ${LULCOBJ} ${TEMOBJ} ${ELMNTOBJ} ${OBJ} xtem606c.cxx 
	${CXX} ${CFLAGS} -o xtem606c ${CLMOBJ} ${LULCOBJ} ${TEMOBJ} ${ELMNTOBJ} ${OBJ} xtem606c.cxx 

xtem606cConstActLayer : ${CLMOBJ} ${LULCOBJ} ${TEMACTOBJ} ${ELMNTACTOBJ} ${OBJ} xtem606cConstActLayer.cxx
	${CXX} ${CFLAGS} -o xtem606cConstActLayer ${CLMOBJ} ${LULCOBJ} ${TEMACTOBJ}  ${ELMNTACTOBJ} ${OBJ} xtem606cConstActLayer.cxx

xtem606cNoFert : ${CLMOBJ} ${LULCOBJ} ${TEMNOFERTOBJ} ${ELMNTNOFERTOBJ} ${OBJ} xtem606cNoFert.cxx
	${CXX} ${CFLAGS} -o xtem606cNoFert ${CLMOBJ} ${LULCOBJ} ${TEMNOFERTOBJ} ${ELMNTNOFERTOBJ} ${OBJ} xtem606cNoFert.cxx

xtem606cNoFert2000 : ${CLMOBJ} ${LULCOBJ} ${TEMNOFERT2000OBJ} ${ELMNTNOFERT2000OBJ} ${OBJ} xtem606cNoFert2000.cxx
	${CXX} ${CFLAGS} -o xtem606cNoFert2000 ${CLMOBJ} ${LULCOBJ} ${TEMNOFERT2000OBJ} ${ELMNTNOFERT2000OBJ} ${OBJ} xtem606cNoFert2000.cxx

xtranalchrt606c : tbiome606.o tprocessXML606.o lulcdat605.o tclmdat606.o tmaxcohortdat605.o ttemdat606.o xtranalchrt606c.cxx
	${CXX} ${CFLAGS} -o xtranalchrt606c tbiome606.o tprocessXML606.o lulcdat605.o tclmdat606.o tmaxcohortdat605.o ttemdat606.o xtranalchrt606c.cxx


atms606b.o : atms606b.cpp atms606b.h
	${CXX} ${CFLAGS} -c atms606b.cpp

elmnt605.o : elmnt605.cpp elmnt605.h
	${CXX} ${CFLAGS} -c elmnt605.cpp

humnact606c.o : humnact606c.cpp humnact606c.h
	${CXX} ${CFLAGS} -c humnact606c.cpp

humnact606cNoFert.o : humnact606cNoFert.cpp humnact606cNoFert.h
	${CXX} ${CFLAGS} -c humnact606cNoFert.cpp

humnact606cNoFert2000.o : humnact606cNoFert2000.cpp humnact606cNoFert2000.h
	${CXX} ${CFLAGS} -c humnact606cNoFert2000.cpp

latdat602.o : latdat602.cpp latdat602.h
	${CXX} ${CFLAGS} -c latdat602.cpp

lulcdat605.o : lulcdat605.cpp lulcdat605.h
	${CXX} ${CFLAGS} -c lulcdat605.cpp

qsoiltemp606b.o : qsoiltemp606b.cpp qsoiltemp606b.h
	${CXX} ${CFLAGS} -c qsoiltemp606b.cpp

tbiome606.o : tbiome606.cpp tbiome606.h
	${CXX} ${CFLAGS} -c tbiome606.cpp

tclm606b.o : tclm606b.cpp tclm606b.h
	${CXX} ${CFLAGS} -c tclm606b.cpp

tclmdat606.o : tclmdat606.cpp tclmdat606.h
	${CXX} ${CFLAGS} -c tclmdat606.cpp

tco2dat437.o : tco2dat437.cpp tco2dat437.h
	${CXX} ${CFLAGS} -c tco2dat437.cpp

telvdat605.o : telvdat605.cpp telvdat605.h
	${CXX} ${CFLAGS} -c telvdat605.cpp

telm606c.o : telm606c.cpp telm606c.h
	${CXX} ${CFLAGS} -c telm606c.cpp

telm606cConstActLayer.o : telm606cConstActLayer.cpp telm606cConstActLayer.h
	${CXX} ${CFLAGS} -c telm606cConstActLayer.cpp

telm606cNoFert.o : telm606cNoFert.cpp telm606cNoFert.h
	${CXX} ${CFLAGS} -c telm606cNoFert.cpp

telm606cNoFert2000.o : telm606cNoFert2000.cpp telm606cNoFert2000.h
	${CXX} ${CFLAGS} -c telm606cNoFert2000.cpp

tlcluc606.o : tlcluc606.cpp tlcluc606.h
	${CXX} ${CFLAGS} -c tlcluc606.cpp

tmaxcohortdat605.o : tmaxcohortdat605.cpp tmaxcohortdat605.h
	${CXX} ${CFLAGS} -c tmaxcohortdat605.cpp

tmcrb606b.o : tmcrb606b.cpp tmcrb606b.h
	${CXX} ${CFLAGS} -c tmcrb606b.cpp

tndepdat605.o : tndepdat605.cpp tndepdat605.h
	${CXX} ${CFLAGS} -c tndepdat605.cpp

tprocessXML606.o : tprocessXML606.cpp tprocessXML606.h
	${CXX} ${CFLAGS} -c tprocessXML606.cpp

tsoil606b.o : tsoil606b.cpp tsoil606b.h
	${CXX} ${CFLAGS} -c tsoil606b.cpp

tsoil606bConstActLayer.o : tsoil606bConstActLayer.cpp tsoil606bConstActLayer.h
	${CXX} ${CFLAGS} -c tsoil606bConstActLayer.cpp

tsoldat606.o : tsoldat606.cpp tsoldat606.h
	${CXX} ${CFLAGS} -c tsoldat606.cpp

ttem606c.o : ttem606c.cpp ttem606c.h
	${CXX} ${CFLAGS} -c ttem606c.cpp

ttem606cConstActLayer.o : ttem606cConstActLayer.cpp ttem606cConstActLayer.h
	${CXX} ${CFLAGS} -c ttem606cConstActLayer.cpp

ttem606cNoFert.o : ttem606cNoFert.cpp ttem606cNoFert.h
	${CXX} ${CFLAGS} -c ttem606cNoFert.cpp

ttem606cNoFert2000.o : ttem606cNoFert2000.cpp ttem606cNoFert2000.h
	${CXX} ${CFLAGS} -c ttem606cNoFert2000.cpp

ttemdat606.o : ttemdat606.cpp ttemdat606.h
	${CXX} ${CFLAGS} -c ttemdat606.cpp

tveg606c.o : tveg606c.cpp tveg606c.h
	${CXX} ${CFLAGS} -c tveg606c.cpp

tveg606cNoFert.o : tveg606cNoFert.cpp tveg606cNoFert.h
	${CXX} ${CFLAGS} -c tveg606cNoFert.cpp

tveg606cNoFert2000.o : tveg606cNoFert2000.cpp tveg606cNoFert2000.h
	${CXX} ${CFLAGS} -c tveg606cNoFert2000.cpp

