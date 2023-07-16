#include <stdio.h>
#include <fcntl.h>  /* Need for functions such as open() */
#include <unistd.h> /* Need for functions such as write(), read() */
#include <string.h> /* Need for functions such as strlen() */

#include "main.h"
#include "errmacros.h"

/** MELODY and TIMING TEMPO
 * melody[] is an array of notes, accompanied by beats[],
 * which sets each note's relative length (higher #, longer note).
 */
int melody[] = {
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_R,
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_R,
    NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_R,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_G5, NOTE_R};

int tempo[] = {
    8, 8, 4, 8,
    8, 8, 4, 8,
    8, 8, 8, 8, 2, 8,
    8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 4, 4, 8};

/* FUNCTION DEFINITION */
int open_element_pwm_file(const char *file_name)
{
    char pathname[DIRECTION_MAX];
    int fd;

    memset(pathname, '\0', DIRECTION_MAX);
    snprintf(pathname, DIRECTION_MAX, "%s%s", PWM_PATH, file_name);
    fd = open(pathname, O_RDWR);
    if (fd < 0)
    {
        perror("File open failed");
        return -1;
    }
    
    #if (DEBUG_LVL > 0)
        printf("%s has already opened successfully\n", pathname);
    #endif

    return fd;
}

int write_element_pwm_file(int fd, int value)
{
    char write_buffer[MSG_SIZE];

    /* Check the parameters */
    if (fd < 0)
    {
        printf("File with fd = %d has not opened yet\n", fd);
        exit(EXIT_FAILURE);
    }

    memset(write_buffer, '\0', MSG_SIZE);
    snprintf(write_buffer, MSG_SIZE, "%d", value);
    write(fd, write_buffer, strlen(write_buffer));

    return THREAD_SUCCESS;
}

int read_element_pwm_file(int fd, void *buf)
{
    /* Check the parameters */
    if (fd < 0)
    {
        printf("File with fd = %d has not opened yet\n", fd);
        exit(EXIT_FAILURE);
    }

    memset(buf, '\0', MSG_SIZE);
    read(fd, buf, MSG_SIZE);

    return THREAD_SUCCESS;
}

void close_element_pwm_file(int fd)
{
    close(fd);
    FILE_CLOSE_ERROR(errno);
}

int main(int argc, char const *argv[])
{
    int num_nodes_of_melody = 0;
    pwm_config_t pwm_config = {
        .duty_cycle_fd = -1,
        .enable_fd = -1,
        .period_fd = -1,
        .enable = 0};

    pwm_config.period_fd = open_element_pwm_file(PERIOD_FILENAME);
    pwm_config.duty_cycle_fd = open_element_pwm_file(DUTY_CYCLE_FILENAME);
    pwm_config.enable_fd = open_element_pwm_file(ENABLE_FILENAME);

    num_nodes_of_melody = sizeof(melody) / sizeof(int);
    printf("Melody has %d nodes\n", num_nodes_of_melody);

    for (int i = 0; i < num_nodes_of_melody; i++)
    {
        int current_node = melody[i];
        int current_tempo = tempo[i];

        if (current_node != NOTE_R)
        {
            pwm_config.period = 1000000000 / current_node;
            pwm_config.duty_cycle = 500000000 / current_node;
            pwm_config.enable = 1;
            write_element_pwm_file(pwm_config.period_fd, pwm_config.period);
            write_element_pwm_file(pwm_config.duty_cycle_fd, pwm_config.duty_cycle);
            write_element_pwm_file(pwm_config.enable_fd, pwm_config.enable);
        }
        else
        {
            pwm_config.enable = 0;
            write_element_pwm_file(pwm_config.enable_fd, pwm_config.enable);
        }

        /* Waiting for playing the current note duration */
        usleep(NOTE_DURATION * 2 / current_tempo);

        /* Disable PWM after playing a note */
        pwm_config.enable = 0;
        write_element_pwm_file(pwm_config.enable_fd, pwm_config.enable);

        /* Waiting 1ms before playing the next note */
        usleep(1000);
    }

    close_element_pwm_file(pwm_config.duty_cycle_fd);
    close_element_pwm_file(pwm_config.enable_fd);
    close_element_pwm_file(pwm_config.period_fd);

    return 0;
}
