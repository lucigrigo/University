package com.luciangrigore;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class Main {

    public static void main(String[] args) {
        try {
//            URI uri = new URI("hello");
//            URI uri = new URI("http://username:password@myserver.com:5000/catalogue/phones?os=android#samsung");
//            URI uri = new URI("/catalogue/phones?os=android#samsung");
//            URI baseURI = new URI("http://username:password@myserver.com:5000");
//            URI resolvedURI = baseURI.resolve(uri);
//
////            URL url = uri.toURL();
//            URL url = resolvedURI.toURL();
//            System.out.println("URL = " + url);
//
//            URI relativizedURI = baseURI.relativize(resolvedURI);
//            System.out.println("Relative URI = " + relativizedURI);

//            System.out.println("Scheme = " + uri.getScheme());
//            System.out.println("Scheme-specific part = " + uri.getSchemeSpecificPart());
//            System.out.println("Authority = " + uri.getAuthority());
//            System.out.println("User info = " + uri.getUserInfo());
//            System.out.println("Host = " + uri.getHost());
//            System.out.println("Port = " + uri.getPort());
//            System.out.println("Path = " + uri.getPath());
//            System.out.println("Query = " + uri.getQuery());
//            System.out.println("Fragment = " + uri.getFragment());

//        } catch (URISyntaxException e) {
//            System.out.println("URI BAD SYNTAX: " + e.getMessage());

//            BufferedReader inputStream = new BufferedReader(new InputStreamReader(url.openStream()));
//
//            String line = "";
//            while (line != null) {
//                line = inputStream.readLine();
//                System.out.println(line);
//            }
//
//            inputStream.close();

//            URL url = new URL("http://example.org/somepage.html");
//            URL url = new URL("http://example.org");
            URL url = new URL("https://api.flickr.com/services/feeds/photos_public.gne?tags=cats");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setRequestProperty("User-Agent", "Chrome");
            connection.setReadTimeout(30000);

            // getResponseCode() implicitly calls the connect() method
            int responseCode = connection.getResponseCode();
            System.out.println("Response code = " + responseCode);

            if (responseCode != 200) {
                System.out.println("Error reading web page");
                System.out.println(connection.getResponseMessage());
                return;
            }

            //  getInputStream() implicitly calls the connect() method
            BufferedReader inputStream = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String line;

            while ((line = inputStream.readLine()) != null) {
                System.out.println(line);
            }

            inputStream.close();

//            urlConnection.setDoOutput(true);
//            urlConnection.connect();
//
//            BufferedReader inputStream = new BufferedReader(new InputStreamReader(urlConnection.getInputStream()));
//            Map<String, List<String>> headerFields = urlConnection.getHeaderFields();
//
//            for (Map.Entry<String, List<String>> entry : headerFields.entrySet()) {
//                String key = entry.getKey();
//                List<String> value = entry.getValue();
//                System.out.println("~~~~~~ key = " + key);
//                for (String value1 : value) {
//                    System.out.println("value = " + value1);
//                }
//            }

//            String line = "";
//            while (line != null) {
//                line = inputStream.readLine();
//                System.out.println(line);
//            }

//            inputStream.close();
        } catch (MalformedURLException e) {
            System.out.println("URL MALFORMED: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IOException: " + e.getMessage());
        }
    }
}
