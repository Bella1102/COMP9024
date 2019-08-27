
typedef struct {
	int day, month, year;
} DateT;

typedef struct {
	int hour, minute;
} TimeT;

typedef struct {
	int   transaction;
	char  weekday[4];        // 3 chars + terminating '\0'
	DateT date;
	TimeT time;
	char  mode;              // 'B', 'F' or 'T'
	char  from[32], to[32];
	int   journey;
	char  faretext[12];
	float fare, discount, amount;
} JourneyT;