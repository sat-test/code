/*

It was like design a Music Player analytics sort of service(in memory), that prints most played song.


void playSong(songId, userId);

void addSong(songId, title);

void printAnalytics();
I was able to code. Then they asked a follow up to add a feature to star/unstar song(s) for a user and get last N favourite songs played(something like that). I wasn't able to fully write the working code for it as time was up.

https://leetcode.com/discuss/interview-experience/5590877/Rippling-SDE-2-Interview-Experience

*/



class Music {
public:
    int songId;
    string title;
    
    Music() {}
    
    Music(int _songId, string _title) {
        songId = _songId;
        title = _title;
    }
};

class MusicSystem {
    unordered_map<int, Music> m;
    unordered_map<int, int> playedMap;
    set<pair<int, int>> orderedMusicPlayedSet;
public:    
    MusicSystem() {
        m.clear();
        playedMap.clear();
        orderedMusicPlayedSet.clear();
    }
    
    void addSong(int songId, string title) {
        if (m.find(songId) == m.end()) {
            m[songId] = Music(songId, title);
        }
    }

    
    void playSong(int songId, int userId) {
        if (m.find(songId) == m.end()) {
            cout << "Song with ID " << songId << " does not exist.\n";
            return;
        }
        
        if (playedMap.find(songId) != playedMap.end()) {
            orderedMusicPlayedSet.erase({playedMap[songId], songId});
        }

        ++playedMap[songId];
        orderedMusicPlayedSet.insert({playedMap[songId], songId});
    }
    
    void printAnalytics() {
        for (auto it = orderedMusicPlayedSet.rbegin(); it != orderedMusicPlayedSet.rend(); ++it) {
            int songId = it->second;
            cout << "Song ID: " << songId << ", Title: " << m[songId].title
                 << ", Plays: " << it->first << "\n";
        }
     }
};


int main() {
    MusicSystem musicSystem;

    musicSystem.addSong(1, "Song A");
    musicSystem.addSong(2, "Song B");
    musicSystem.addSong(3, "Song C");

    musicSystem.playSong(1, 101);
    musicSystem.playSong(2, 102);
    musicSystem.playSong(1, 101);
    musicSystem.playSong(3, 103);
    musicSystem.playSong(2, 102);
    musicSystem.playSong(1, 101);

    cout << "Analytics:\n";
    musicSystem.printAnalytics();

    return 0;
}
