package com.luciangrigore;

import com.luciangrigore.model.Artist;
import com.luciangrigore.model.DataSource;
import com.luciangrigore.model.SongArtist;

import java.util.List;

public class Main {

    public static void main(String[] args) {
        DataSource dataSource = new DataSource();
        if (!dataSource.open()) {
            System.out.println("can't open datasource!");
            return;
        }

        List<Artist> artistList = dataSource.queryArtists(DataSource.ORDER_BY_NONE);
        if (artistList == null) {
            System.out.println("no artists");
        } else {
            for (Artist artist : artistList) {
                System.out.println("ID = " + artist.getId() + ". Name = " + artist.getName());
            }
        }

        System.out.println("\n\n\n========================\n\n\n");
        List<String> albumsPinkFloyd = dataSource.queryAlbumsForArtist("Pink Floyd", DataSource.ORDER_BY_ASC);
        if (albumsPinkFloyd == null) {
            System.out.println("no albums");
        } else {
            for (String name : albumsPinkFloyd) {
                System.out.println(name);
            }
        }

        System.out.println("\n\n\n========================\n\n\n");
        String song = "She's On Fire";
        List<SongArtist> songArtists = dataSource.queryArtistForSong(song, DataSource.ORDER_BY_ASC);
        if (songArtists == null) {
            System.out.println("no data");
        } else {
            for (SongArtist songArtist : songArtists) {
                System.out.println("SONG: " + song + " | TRACK_NUMBER: " + songArtist.getTrack()
                        + " | ARTIST_NAME: " + songArtist.getArtistName() + " | ALBUM_NAME: " + songArtist.getAlbumName());
            }
        }

        System.out.println("\n\n\n========================\n\n\n");
        dataSource.querySongsMetaData();

        dataSource.close();
    }
}
