package sample.model;

import javafx.scene.chart.PieChart;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DataSource {
    public static final String DB_NAME = "music.db";

    public static final String CONNECTION_STRING = "jdbc:sqlite:/Users/grigorelucian/Documents/CompleteJavaMasterclassUDEMY/MusicUI/" + DB_NAME;

    public static final String TABLE_ALBUMS = "albums";
    public static final String COLUMN_ALBUM_ID = "_id";
    public static final String COLUMN_ALBUM_NAME = "name";
    public static final String COLUMN_ALBUM_ARTIST = "artist";
    public static final int INDEX_ALBUM_ID = 1;
    public static final int INDEX_ALBUM_NAME = 2;
    public static final int INDEX_ALBUM_ARTISTS = 3;

    public static final String TABLE_ARTISTS = "artists";
    public static final String COLUMN_ARTIST_ID = "_id";
    public static final String COLUMN_ARTIST_NAME = "name";
    public static final int INDEX_ARTIST_ID = 1;
    public static final int INDEX_ARTIST_NAME = 2;

    public static final String TABLE_SONGS = "songs";
    public static final String COLUMN_SONG_ID = "_id";
    public static final String COLUMN_SONG_TRACK = "track";
    public static final String COLUMN_SONG_TITLE = "title";
    public static final String COLUMN_SONG_ALBUM = "album";
    public static final int INDEX_SONG_ID = 1;
    public static final int INDEX_SONG_TRACK = 2;
    public static final int INDEX_SONG_TITLE = 3;
    public static final int INDEX_SONGS_ALBUM = 4;

    public static final int ORDER_BY_NONE = 1;
    public static final int ORDER_BY_ASC = 2;
    public static final int ORDER_BY_DESC = 3;

    public static final String QUERY_ALBUMS_BY_ARTIST_START =
            "SELECT " + TABLE_ALBUMS + '.' + COLUMN_ALBUM_NAME + " FROM " + TABLE_ALBUMS + " INNER JOIN " +
                    TABLE_ARTISTS + " ON " + TABLE_ALBUMS + '.' + COLUMN_ALBUM_ARTIST + "=" + TABLE_ARTISTS +
                    '.' + COLUMN_ARTIST_ID + " WHERE " + TABLE_ARTISTS + '.' + COLUMN_ARTIST_NAME + " = \"";
    public static final String QUERY_ALBUMS_BY_ARTIST_SORT =
            " ORDER BY " + TABLE_ALBUMS + '.' + COLUMN_ALBUM_NAME
                    + " COLLATE NOCASE ";
    public static final String QUERY_ARTIST_FOR_SONG_START =
            "SELECT " + TABLE_ARTISTS + '.' + COLUMN_ARTIST_NAME + ',' + TABLE_SONGS + '.' + COLUMN_SONG_TRACK +
                    ',' + TABLE_ALBUMS + '.' + COLUMN_ALBUM_NAME + " FROM " + TABLE_SONGS + " INNER JOIN " +
                    TABLE_ALBUMS + " ON " + TABLE_SONGS + '.' + COLUMN_SONG_ALBUM + '=' + TABLE_ALBUMS + '.' +
                    COLUMN_ALBUM_ID + " INNER JOIN " + TABLE_ARTISTS + " ON " + TABLE_ARTISTS + '.' + COLUMN_ARTIST_ID +
                    '=' + TABLE_ALBUMS + '.' + COLUMN_ALBUM_ARTIST + " WHERE " + TABLE_SONGS + '.' + COLUMN_SONG_TITLE +
                    "=\"";
    public static final String QUERY_ARTIST_FOR_SONG_SORT =
            " ORDER BY " + TABLE_ARTISTS + '.' + COLUMN_ARTIST_NAME + ',' + TABLE_ALBUMS + '.' + COLUMN_ALBUM_NAME +
                    " COLLATE NOCASE ";
    public static final String TABLE_ARTIST_SONG_VIEW = "artist_list";
    public static final String CREATE_ARTIST_FOR_SONG = "CREATE VIEW IF NOT EXISTS " + TABLE_ARTIST_SONG_VIEW +
            " AS SELECT " + TABLE_ARTISTS + '.' + COLUMN_ARTIST_NAME + ',' + TABLE_ALBUMS + '.' + COLUMN_ALBUM_NAME +
            " AS album, " + TABLE_SONGS + '.' + COLUMN_SONG_TRACK + ',' + TABLE_SONGS + '.' + COLUMN_SONG_TITLE +
            " FROM " + TABLE_SONGS + " INNER JOIN " + TABLE_ALBUMS + " ON " + TABLE_SONGS + '.' + COLUMN_SONG_ALBUM +
            '=' + TABLE_ALBUMS + '.' + COLUMN_ALBUM_ID + " INNER JOIN " + TABLE_ARTISTS + " ON " + TABLE_ALBUMS + '.' +
            COLUMN_ALBUM_ARTIST + '=' + TABLE_ARTISTS + '.' + COLUMN_ARTIST_ID + " ORDER BY " + TABLE_ARTISTS + '.' +
            COLUMN_ARTIST_NAME + ',' + TABLE_ALBUMS + '.' + COLUMN_ALBUM_NAME + ',' + TABLE_SONGS + '.' + COLUMN_SONG_TRACK;
    public static final String CREATE_VIEW_SONG_INFO = "SELECT " + COLUMN_ARTIST_NAME + ',' + COLUMN_SONG_ALBUM + ',' +
            COLUMN_SONG_TRACK + " FROM " + TABLE_ARTIST_SONG_VIEW + " WHERE " + COLUMN_SONG_TITLE + "=\"";
    public static final String QUERY_VIEW_SONG_INFO_PREP = "SELECT " + COLUMN_ARTIST_NAME + ',' + COLUMN_SONG_ALBUM + ',' +
            COLUMN_SONG_TRACK + " FROM " + TABLE_ARTIST_SONG_VIEW + " WHERE " + COLUMN_SONG_TITLE + " = ?";
    public static final String QUERY_ARTISTS = "SELECT " + COLUMN_ARTIST_ID + " FROM " + TABLE_ARTISTS +
            " WHERE " + COLUMN_ARTIST_NAME + " = ?";
    public static final String QUERY_ALBUM = "SELECT " + COLUMN_ALBUM_ID + " FROM " + TABLE_ALBUMS + " WHERE " +
            COLUMN_ALBUM_NAME + " = ?";
    public static final String QUERY_ALBUMS_BY_ARTIST_ID = "SELECT * FROM " + TABLE_ALBUMS + " WHERE " + COLUMN_ALBUM_ARTIST +
            " = ? ORDER BY " + COLUMN_ALBUM_NAME + " COLLATE NOCASE";
    public static final String UPDATE_ARTIST_NAME = "UPDATE " + TABLE_ARTISTS + " SET " + COLUMN_ARTIST_NAME + " = ? WHERE " +
            COLUMN_ARTIST_ID + " = ?";

    public static final String INSERT_ARTISTS = "INSERT INTO " + TABLE_ARTISTS + '(' + COLUMN_ARTIST_NAME + ") VALUES(?)";
    public static final String INSERT_ALBUMS = "INSERT INTO " + TABLE_ALBUMS + "(" + COLUMN_ALBUM_NAME + ", " +
            COLUMN_ALBUM_ARTIST + ") VALUES(?, ?)";
    public static final String INSERT_SONGS = "INSERT INTO " + TABLE_SONGS + '(' + COLUMN_SONG_TRACK + ", " +
            COLUMN_SONG_TITLE + ", " + COLUMN_SONG_ALBUM + ") VALUES(?, ?, ?)";

    private Connection conn;
    private PreparedStatement querySongInfoView;
    private PreparedStatement insertIntoArtists;
    private PreparedStatement insertIntoAlbums;
    private PreparedStatement insertIntoSongs;
    private PreparedStatement queryArtist;
    private PreparedStatement queryAlbum;
    private PreparedStatement queryAlbumsByArtistId;
    private PreparedStatement updateArtistName;

    private static DataSource instance = new DataSource();

    private DataSource() {

    }

    public static DataSource getInstance() {
        return instance;
    }

    public boolean open() {
        try {
            conn = DriverManager.getConnection(CONNECTION_STRING);
            querySongInfoView = conn.prepareStatement(QUERY_VIEW_SONG_INFO_PREP);
            insertIntoArtists = conn.prepareStatement(INSERT_ARTISTS, Statement.RETURN_GENERATED_KEYS);
            insertIntoAlbums = conn.prepareStatement(INSERT_ALBUMS, Statement.RETURN_GENERATED_KEYS);
            insertIntoSongs = conn.prepareStatement(INSERT_SONGS);
            queryArtist = conn.prepareStatement(QUERY_ARTISTS);
            queryAlbum = conn.prepareStatement(QUERY_ALBUM);
            queryAlbumsByArtistId = conn.prepareStatement(QUERY_ALBUMS_BY_ARTIST_ID);
            updateArtistName = conn.prepareStatement(UPDATE_ARTIST_NAME);

            return true;
        } catch (SQLException e) {
            System.out.println("something went wrong! " + e.getMessage());
            return false;
        }
    }

    public void close() {
        try {
            if (conn != null) {
                conn.close();
            }
            if (querySongInfoView != null) {
                querySongInfoView.close();
            }
            if (insertIntoSongs != null) {
                insertIntoSongs.close();
            }
            if (insertIntoAlbums != null) {
                insertIntoAlbums.close();
            }
            if (insertIntoArtists != null) {
                insertIntoArtists.close();
            }
            if (queryAlbum != null) {
                queryAlbum.close();
            }
            if (queryArtist != null) {
                queryArtist.close();
            }
            if (queryAlbumsByArtistId != null) {
                queryAlbumsByArtistId.close();
            }
            if (updateArtistName != null) {
                updateArtistName.close();
            }
        } catch (SQLException e) {
            System.out.println("something went wrong! " + e.getMessage());
        }
    }

    public boolean updateArtistName(int id, String name) {
        try {
            updateArtistName.setString(1, name);
            updateArtistName.setInt(2, id);
            int affectedRows = updateArtistName.executeUpdate();

            return affectedRows == 1;
        } catch (SQLException e) {
            System.out.println("Update Failed! " + e.getMessage());
            return false;
        }
    }

    public List<Artist> queryArtists(int sortOrder) {
        StringBuilder sb = new StringBuilder("SELECT * FROM ");

        sb.append(TABLE_ARTISTS);
        if (sortOrder != ORDER_BY_NONE) {
            sb.append(" ORDER BY ");
            sb.append(COLUMN_ARTIST_NAME);
            sb.append(" COLLATE NOCASE ");
            if (sortOrder == ORDER_BY_DESC) {
                sb.append("DESC");
            } else {
                //  default -> ascending order
                sb.append("ASC");
            }
        }

        try (Statement statement = conn.createStatement();
             ResultSet resultSet = statement.executeQuery(sb.toString())) {

            List<Artist> artists = new ArrayList<>();
            while (resultSet.next()) {
                try {
                    Thread.sleep(20);
                } catch (InterruptedException e) {
                    System.out.println("Interrupted: " + e.getMessage());
                }

                Artist artist = new Artist();
                artist.setId(resultSet.getInt(INDEX_ARTIST_ID));
                artist.setName(resultSet.getString(INDEX_ARTIST_NAME));
                artists.add(artist);
            }

            return artists;
        } catch (SQLException e) {
            System.out.println("query failed! " + e.getMessage());
            return null;
        }
    }

    public List<String> queryAlbumsForArtist(String artistName, int sortOrder) {
        StringBuilder sb = new StringBuilder(QUERY_ALBUMS_BY_ARTIST_START);
        sb.append(artistName);
        sb.append("\"");

        if (sortOrder != ORDER_BY_NONE) {
            sb.append(QUERY_ALBUMS_BY_ARTIST_SORT);
            if (sortOrder == ORDER_BY_DESC) {
                sb.append("DESC");
            } else {
                sb.append("ASC");
            }
        }

        System.out.println("SQL statement = " + sb.toString());

        try (Statement statement = conn.createStatement();
             ResultSet resultSet = statement.executeQuery(sb.toString())) {
            List<String> albums = new ArrayList<>();

            while (resultSet.next()) {
                albums.add(resultSet.getString(1));
            }

            return albums;
        } catch (SQLException e) {
            System.out.println("query failed! : " + e.getMessage());
            return null;
        }
    }

    public void querySongsMetaData() {
        String sql = "SELECT * FROM " + TABLE_SONGS;
        try (Statement statement = conn.createStatement();
             ResultSet resultSet = statement.executeQuery(sql)) {
            ResultSetMetaData resultSetMetaData = resultSet.getMetaData();

            int numColumns = resultSetMetaData.getColumnCount();
            for (int i = 1; i <= numColumns; i++) {
                System.out.format("Column %d in the songs table is %s\n", i, resultSetMetaData.getColumnName(i));
            }
        } catch (SQLException e) {
            System.out.println("error! " + e.getMessage());
        }
    }

    public int getcount(String table) {
        String sql = "SELECT COUNT(*) AS count FROM " + table;
        try (Statement statement = conn.createStatement();
             ResultSet resultSet = statement.executeQuery(sql)) {
            int count = resultSet.getInt("count");

            System.out.printf("Count is %d.\n", count);
            return count;
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            return 0;
        }
    }

    public boolean createViewForSongArtist() {
        try (Statement statement = conn.createStatement()) {
            statement.execute(CREATE_ARTIST_FOR_SONG);
            return true;
        } catch (SQLException e) {
            System.out.println("view not created! " + e.getMessage());
            return false;
        }
    }

    private int insertArtist(String artistName) throws SQLException {
        queryArtist.setString(1, artistName);
        ResultSet resultSet = queryArtist.executeQuery();
        // CHECK FOR EXISTING ARTIST
        if (resultSet.next()) {
            return resultSet.getInt(1);
        } else {
            // INSERT THE ARTIST
            insertIntoArtists.setString(1, artistName);
            int affectedRows = insertIntoArtists.executeUpdate();
            if (affectedRows != 1) {
                throw new SQLException("could not insert artist");
            }

            ResultSet generatedKeys = insertIntoArtists.getGeneratedKeys();
            if (generatedKeys.next()) {
                return generatedKeys.getInt(1);
            } else {
                throw new SQLException("could not get _id for artist");
            }
        }
    }

    private int insertAlbum(String albumName, int artistId) throws SQLException {
        queryAlbum.setString(1, albumName);
        ResultSet resultSet = queryAlbum.executeQuery();
        // CHECK FOR EXISTING ALBUM
        if (resultSet.next()) {
            return resultSet.getInt(1);
        } else {
            // INSERT THE ALBUM
            insertIntoAlbums.setString(1, albumName);
            insertIntoAlbums.setInt(2, artistId);
            int affectedRows = insertIntoAlbums.executeUpdate();

            if (affectedRows != 1) {
                throw new SQLException("could not insert album");
            }

            ResultSet generatedKeys = insertIntoAlbums.getGeneratedKeys();
            if (generatedKeys.next()) {
                return generatedKeys.getInt(1);
            } else {
                throw new SQLException("could not get _id for album");
            }
        }
    }

    public void insertSong(String title, String artist, String album, int track) {
        try {
            conn.setAutoCommit(false);

            int artistId = insertArtist(artist);
            int albumId = insertAlbum(album, artistId);
            insertIntoSongs.setInt(1, track);
            insertIntoSongs.setString(2, title);
            insertIntoSongs.setInt(3, albumId);
            int affectedRows = insertIntoSongs.executeUpdate();
            if (affectedRows == 1) {
                conn.commit();
            } else {
                throw new SQLException("song insert failed!");
            }
        } catch (Exception e) {
            System.out.println("could not insert song! " + e.getMessage());
            try {
                System.out.println("performing rollback . . .");
                conn.rollback();
            } catch (SQLException e2) {
                System.out.println("rollback failed! " + e2.getMessage());
            }
        } finally {
            try {
                System.out.println("resetting default commit behaviour");
                conn.setAutoCommit(true);
            } catch (SQLException e3) {
                System.out.println("could not reset auto-commit! " + e3.getMessage());
            }
        }
    }

    public List<Album> queryAlbumForArtistId(int id) {
        try {
            queryAlbumsByArtistId.setInt(1, id);
            ResultSet resultSet = queryAlbum.executeQuery();
            List<Album> list = new ArrayList<>();

            while (resultSet.next()) {
                Album album = new Album();
                album.setArtistId(resultSet.getInt(id));
                album.setName(resultSet.getString(2));
                album.setId(resultSet.getInt(1));
                list.add(album);
            }

            return list;
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            return null;
        }
    }
}

