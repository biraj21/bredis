CC = cc
FLAGS = -Wall -Werror -Wpedantic -Wextra

src_dir = src
client_src = $(src_dir)/client
server_src = $(src_dir)/server
shared_src = $(src_dir)/shared

obj_dir = obj
client_obj = $(obj_dir)/client
server_obj = $(obj_dir)/server
shared_obj = $(obj_dir)/shared

dist_dir = dist
client_bin = $(dist_dir)/client
server_bin = $(dist_dir)/server

client_header_files = $(wildcard $(client_src)/*.h)
server_header_files = $(wildcard $(server_src)/*.h)
shared_header_files = $(wildcard $(shared_src)/*.h)

client_obj_files = $(patsubst $(client_src)/%.c, $(client_obj)/%.o, $(wildcard $(client_src)/*.c))
server_obj_files = $(patsubst $(server_src)/%.c, $(server_obj)/%.o, $(wildcard $(server_src)/*.c))
shared_obj_files = $(patsubst $(shared_src)/%.c, $(shared_obj)/%.o, $(wildcard $(shared_src)/*.c))

all: clean dist-setup $(client_bin) $(server_bin)

dist-setup:
	mkdir -p $(client_obj) $(server_obj) $(shared_obj) $(dist_dir)

# clean up by deleting binaries & object files
clean:
	rm -fr $(obj_dir) $(dist_dir)

# create client binary by stitching client's & shared object files
$(client_bin): $(client_obj_files) $(shared_obj_files)
	$(CC) $(FLAGS) -o $@ $^

# create server binary by stitching server's & shared object files
$(server_bin): $(server_obj_files) $(shared_obj_files)
	$(CC) $(FLAGS) -o $@ $^

# compile a .c file when it or any related header file has changed

$(client_obj)/%.o: $(client_src)/%.c $(client_header_files) $(shared_header_files)
	$(CC) $(FLAGS) -c -o $@ $<

$(server_obj)/%.o: $(server_src)/%.c $(server_header_files) $(shared_header_files)
	$(CC) $(FLAGS) -c -o $@ $<

$(shared_obj)/%.o: $(shared_src)/%.c $(shared_src)/%.h
	$(CC) $(FLAGS) -c -o $@ $<

# debug: $(server_bin)
# 	valgrind --log-file=valgrind.log $(server_bin)

