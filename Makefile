all: 
	gcc -g cronjob.c up_exec.c echo.c env_var.c jobs.c piping.c input_handling.c junction.c display.c cd.c ls.c system.c pinfo.c history.c nightswatch.c redirect.c handlers.c main.c -o shell
