CC = mpicc
RM = /bin/rm -rf
TARGET = main
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
CFLAGS=-g -Og -Wall -Werror -Wextra
LDFLAGS=-g -Og -Wall -Werror -Wextra

##############################################

all:		$(TARGET)

install: 	$(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET):	$(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
	$(RM) $(OBJS) $(TARGET) skel profile.*

test: $(TARGET)
	$(RM) pooky2
	#mpirun -np 4 tau_exec -T mpi -io -skel ./$(TARGET)
	mpirun -np 4 tau_exec -T mpi ./$(TARGET)
##############################################
