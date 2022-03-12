/***** Design Book my show *****/
/****
Requirements
1. List down theatres in a city
2. List down movies in a city
3. List of cities
4. For a theatre, show all screen and moview on it
5. User profile/account
6. Book ticket
7. Payment
****/

class UserProfile {
    int     userId;
    string  userName;
    string  contactNum;
    string  passWord;
    string  emailId;
};

class Admin {
    int     adminId;
    string  adminName;
    string  contactNum;
    string  passWord;
    string  emailId;
};

class Theatre {
    string theatreName;
    int numScreen;
    string address;
    int pinCode;
    unordered_map <int, Screen> movieToscreensMap;

public:
    vector <Movie>& getAllMovies();
    vector <Screen>& getAllScreens();
    void SetMovieForScreen(const int& movieId, const int& screenId);
    const Seat**        GetMovieSeatingDetails(const int& movieId) {
        auto screen = movieToscreensMap[movieId];
        return screen.GetSeatMap();
    }
    int BookSeats(const int& movieId, const vector<pair<int,int>> seats) {
        auto screen = movieToscreensMap[movieId];
        return screen.BookSeats(seats);
    }
    // void addScreen(int seatingCap, )
};

class Movie {
    int                     movieId;
    string                  name;
    string                  description;
    int                     duration;
    string                  castDetails;
    unordered_set <string>  availableLanguages;

public:
    string GetMovieName() {
        return name;
    }
};

constexpr int MAX_ROW = 100;
constexpr int MAX_COL = 100;

class Seat {
    int seatType;
    int price;
    bool isBooked;
public:
    bool BookSeat() {
        if (isBooked) return false;
        isBooked = true;
    }

    int GetPrice() {
        return price;
    }
};

class Screen {
    int screenId;
    int seatingCap;
    int bookedSeats;
    Seat seatMap[MAX_ROW][MAX_COL];
    Movie movie;
public:
    int BookSeat(int r, int c);
    int vacantSeat(int r, int c);
    int setMovie(const Movie& movie);
    int BookSeats(const vector<pair<int,int>> seats) {
        int totalPrice = 0;
        for(auto x : seats) {
            auto seat = seatMap[x.first][x.second];
            if (seat.BookSeat()) {
                totalPrice += seat.GetPrice();
            }
            else {
                return -1;
            }
        }
        return totalPrice;
    }
    const Seat** GetSeatMap() {
        return seatMap;
    }
};

class BookMyShowApp {
    unordered_map <string, CityData>    cities;
    unordered_map <int, Movie>          movieDb;
    string                              selectedCity;
    User                                currUser;

    void                Login();
    void                CreateAccount();
    void                SelectCity(const string& city);
    vector<Movie>       GetAllMoviesInTheatre(const int& theatreId);
    vector<Movie>       GetAllMoviesInACity();
    vector<Theatre>     GetAllTheatresInACity();
    vector<Theatre>     GetAllTheatresForMovie(const int& movieId);
    const Movie&        GetMovieDetails(const int& movieId);
    const Seat**        GetMovieSeatingDetails(const int& movieId, const int& theatreId);
    void                SetMovieDetails(const Movie& movie);
    void                BookTickets(const int& theatreId, const int& movieId, const vector<pair<int,int>> seats) {
        CityData selectedCityData = cities[selectedCity];
        auto theatre = selectedCityData.GetTheatre(theatreId);
        // Check if Seats are available
        int totalPrice = theatre.BookSeats(movieId, seats);
        if (totalPrice > 0) {
            int ret = currUser->Pay(totalPrice);
            
            // Payment failed
            if (ret < 0) {
                theatre.UnBlockSeats(movieId, seats);
                cout << "Payment failed. Retry your payment." << endl;
            }
            else {
                cout << "Congratulations..your tickets for " << movieDb[movieId].GetMovieName() << " are booked" << endl;
            }
        }
        else {
            cout << "Seats are not available. Make another selection" << endl;
        }
    }
};

class CityData {
    int                             cityId;
    string                          cityName;
    string                          stateName;
    string                          countryName;
    unordered_map <int, Theatre>    theatres;

public:
    void                AddTheatre();
    const Theatre&      GetTheatre(const int& theatreId);
    vector<Theatre>     GetAllTheatres();
    vector<Theatre>     GetAllTheatresForMovie(const int& movieId);
    vector<Movie>       GetAllMovies();
    const Seat**        GetMovieSeatingDetails(const int& movieId, const int& theatreId);
};