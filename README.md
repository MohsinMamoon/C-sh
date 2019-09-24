# C-sh

## Files:
<dl>
<dt> main.c </dt>
<dd> This file contains the main shell loop. <br> It reads user input and calls the necessary functions to parse the input and figure out the command to be executed. </dd>

<dt> input_handling.c </dt>
<dd> This file contains the code for parsing the input. It parses the input into different commands and parses the commands into different arguments. </dd>

<dt> defs.h </dt>
<dd> This file contains the declarations of the functions used in the shell. </dd>

<dt> display.c </dt>
<dd> This file contains definitions for the functions related to display the shell prompt. </dd>

<dt> handlers.c </dt>
<dd> This file contains the definitons for the functions dealing with signal handling. </dd>

<dt> junction.c </dt>
<dd> This file contains code to figure out the command to be executed and after some preprocessing (if needed) like redirection setup, call the corresponding function. </dd>

<dt> Rest </dt>
<dd> Rest of the files contain code for implementation of the command\feature implied by the file name.</dd>
</dl>


## Commands Supported:
<dl>
<dt> clear </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Clears the terminal screen</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li> <code>clear</code> </li>
                <li> <code>Ctrl-L</code> </li>
        </dd>
    </dl>
</dd>
<dt> quit </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Exits the shell</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li> <code>quit</code> </li>
                <li> <code>exit</code> </li>
                <li> <code>q</code> </li>
        </dd>
    </dl>
</dd>
<dt> ls </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Basic implementation of ls. Supprts 'a' and 'l' flags.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>ls [-al] [dir\file path]</code></li>
            </ul>
        </dd>
        <dt>Note: </dt>
        <dd>
            <ul>
                <li>If path is not given, path will be set to '.'.</li>
                <li>Paths with spaces also supported. (Enclose in ""). </li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> cd </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Basic implementation of cd.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>cd [directory]</code> </li>
            </ul>
        </dd>
        <dt>Note: </dt>
        <dd>
            <ul>
                <li>If directory is omitted, '~' will be treated as directory.</li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> echo </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Basic implementation of echo.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>echo < phrase ></code> </li>
            </ul>
        </dd>
        <dt>Note: </dt>
        <dd>
            <ul>
                <li>Regex not supported. </li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> pwd </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Basic implementation of pwd.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>pwd</code></li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> pinfo </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Gives information (pid, status, executable path, etc) about a given process.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>pinfo [pid]</code></li>
            </ul>
        </dd>
        <dt>Note: </dt>
        <dd>
            <ul>
                <li>If pid is omitted, pid of shell is used.</li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> nightswatch </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Perodically displays the number of times the cpu has been interrupted by the keyboard (interrupt) or the size of part of memory which is dirty (dirty).</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>nightswatch -n < seconds > < mode ></code></li>
            </ul>
        </dd>
        <dt>Options: </dt>
        <dd>
            <ul>
                <li>seconds: Time interval for repitition.</li>
                <li>mode: 'interrupt' or 'dirty'. </li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> history </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Displays the past commands.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>history [number]</code></li>
            </ul>
        </dd>
        <dt>Options: </dt>
        <dd>
            <ul>
                <li>number: Number of commands to display. [0-20]</li>
            </ul>
        </dd>
        <dt>Note: </dt>
        <dd>
            <ul>
                <li>If number is omitted, 10 commands are displayed.</li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> jobs </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Lists all the background jobs currently running.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>jobs</code></li>
            </ul>
        </dd>
        <dt>Note: </dt>
    </dl>
</dd>
<dt> kjob </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Sends a given signal to the given job. </dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>kjob < job > < signal ></code></li>
            </ul>
        </dd>
        <dt>Options: </dt>
        <dd>
            <ul>
                <li>job: job number</li>
                <li>signal: signal number to be sent </li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> fg </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Change the status of given job from background to foreground. </dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>fg [job]</code></li>
            </ul>
        </dd>
        <dt>Options: </dt>
        <dd>
            <ul>
                <li>job: job number</li>
            </ul>
        </dd>
        <dt>Note: </dt>
        <dd>
            <ul>
                <li>If job is omitted, the latest job is considered. </li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> bg </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Change the status of a job from stopped in background to running in background. </dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>bg [job]</code></li>
            </ul>
        </dd>
        <dt>Options: </dt>
        <dd>
            <ul>
                <li>job: job number</li>
            </ul>
        </dd>
        <dt>Note: </dt>
        <dd>
            <ul>
                <li>If job is omitted, latest job is considered.</li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> overkill </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Terminate all jobs running in the background.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>overkill</code></li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> getenv </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Get the value of an environment variable.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>getenv < env ></code></li>
            </ul>
        </dd>
        <dt>Options: </dt>
        <dd>
            <ul>
                <li>env: Environment variable</li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> setenv </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Set the value of an environment variable.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>setenv < env > < value ></code> </li>
            </ul>
        </dd>
        <dt>Options: </dt>
        <dd>
            <ul>
                <li>env: Environment vairable.</li>
                <li>value: Value to set env to.</li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> unsetenv </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Unset environment variable.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>unsetenv < env ></code></li>
            </ul>
        </dd>
        <dt>Options: </dt>
        <dd>
            <ul>
                <li>env: Environment variable.</li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> cronjob </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Run a command periodically for a given amount of time.</dd>
        <dt>Syntax: </dt>
        <dd>
            <ul>
                <li><code>cronjob -c < command > -t < period > -p < total ></code></li>
            </ul>
        </dd>
        <dt>Options: </dt>
        <dd>
            <ul>
                <li>command: command to be run.</li>
                <li>period: Time (seconds) after which to run the command again.</li>
                <li>total: total time for which the command is to be run.</li>
            </ul>
        </dd>
    </dl>
</dd>
<dt> Other </dt>
<dd>
    <dl>
        <dt>Function: </dt>
        <dd>Runs all the other shell commands using execvp.</dd>
    </dl>
</dd>
</dl>


## Features:
<dl>
<dt> Piping </dt>
<dt> Redirection </dt>
<dt> Command recall using 'UP' key </dt>
<dt> Job control </dt>
<dd> Supports foreground and background processes. Supports switching a proccess from background to foreground and vice versa. </dd>
<dt> Signal Handling </dt>
<dd> Ctrl-Z and Ctrl-C have no effect in main shell but when a command is running, Ctrl-C sends SIGSTOP to it and Ctrl-Z sends it to background. </dd>
</dl>


## Running:
<ol>
<li> Clone this repository: <code>git clone addr</code> </li>
<li> Cd into the directory: <code>cd C-sh</code> </li>
<li> Compile the code: <code>make</code> </li>
<li> Run the shell: <code>./shell</code> </li>
</ol>
