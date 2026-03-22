#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

struct MusicPlayer;
typedef struct PlayerState PlayerState;

struct PlayerState
{
    void (*pressPlay)(PlayerState *state);
    void (*pressPause)(PlayerState *state);
    void (*pressStop)(PlayerState *state);
    void (*setContext)(PlayerState *state, struct MusicPlayer *player); // Môi 1 state cụ thể sẽ tự chuyển đổi state trong context khi các nut tương ứng bấm.

    struct MusicPlayer *player;
};

#endif // PLAYER_STATE_H