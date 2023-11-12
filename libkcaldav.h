/*
 * Copyright (c) Kristaps Dzonsons <kristaps@bsd.lv>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#ifndef LIBKCALDAV_H
#define LIBKCALDAV_H

#if !defined(__BEGIN_DECLS)
#  ifdef __cplusplus
#  define       __BEGIN_DECLS           extern "C" {
#  else
#  define       __BEGIN_DECLS
#  endif
#endif
#if !defined(__END_DECLS)
#  ifdef __cplusplus
#  define       __END_DECLS             }
#  else
#  define       __END_DECLS
#  endif
#endif

enum	calreqtype {
	CALREQTYPE_CALMULTIGET,
	CALREQTYPE_CALQUERY,
	CALREQTYPE_PROPERTYUPDATE,
	CALREQTYPE_PROPFIND,
};

enum	calelem {
	CALELEM_CALENDAR_COLOR,
	CALELEM_CALENDAR_DATA,
	CALELEM_CALENDAR_DESCRIPTION,
	CALELEM_CALENDAR_HOME_SET,
	CALELEM_MIN_DATE_TIME,
	CALELEM_CALENDAR_MULTIGET,
	CALELEM_CALENDAR_PROXY_READ_FOR,
	CALELEM_CALENDAR_PROXY_WRITE_FOR,
	CALELEM_CALENDAR_QUERY,
	CALELEM_CALENDAR_TIMEZONE,
	CALELEM_CALENDAR_USER_ADDRESS_SET,
	CALELEM_CURRENT_USER_PRINCIPAL,
	CALELEM_CURRENT_USER_PRIVILEGE_SET,
	CALELEM_DISPLAYNAME,
	CALELEM_GETCONTENTTYPE,
	CALELEM_GETCTAG,
	CALELEM_GETETAG,
	CALELEM_GROUP_MEMBER_SET,
	CALELEM_GROUP_MEMBERSHIP,
	CALELEM_HREF,
	CALELEM_OWNER,
	CALELEM_PRINCIPAL_URL,
	CALELEM_PROP,
	CALELEM_PROPERTYUPDATE,
	CALELEM_PROPFIND,
	CALELEM_QUOTA_AVAILABLE_BYTES,
	CALELEM_QUOTA_USED_BYTES,
	CALELEM_RESOURCETYPE,
	CALELEM_SCHEDULE_CALENDAR_TRANSP,
	CALELEM_SUPPORTED_CALENDAR_COMPONENT_SET,
	CALELEM_SUPPORTED_CALENDAR_DATA,
	CALELEM__MAX
};

/*
 * Each of the property types within <DAV::prop> elements that we
 * support.
 */
enum	calproptype {
	CALPROP_CALENDAR_COLOR,
	CALPROP_CALENDAR_DATA,
	CALPROP_CALENDAR_DESCRIPTION,
	CALPROP_CALENDAR_HOME_SET,
	CALPROP_MIN_DATE_TIME,
	CALPROP_CALENDAR_PROXY_READ_FOR,
	CALPROP_CALENDAR_PROXY_WRITE_FOR,
	CALPROP_CALENDAR_TIMEZONE,
	CALPROP_CALENDAR_USER_ADDRESS_SET,
	CALPROP_CURRENT_USER_PRINCIPAL,
	CALPROP_CURRENT_USER_PRIVILEGE_SET,
	CALPROP_DISPLAYNAME,
	CALPROP_GETCONTENTTYPE,
	CALPROP_GETCTAG,
	CALPROP_GETETAG,
	CALPROP_GROUP_MEMBER_SET,
	CALPROP_GROUP_MEMBERSHIP,
	CALPROP_OWNER,
	CALPROP_PRINCIPAL_URL,
	CALPROP_QUOTA_AVAILABLE_BYTES,
	CALPROP_QUOTA_USED_BYTES,
	CALPROP_RESOURCETYPE,
	CALPROP_SCHEDULE_CALENDAR_TRANSP,
	CALPROP_SUPPORTED_CALENDAR_COMPONENT_SET,
	CALPROP_SUPPORTED_CALENDAR_DATA,
	CALPROP__MAX
};

enum	icaltype {
	ICALTYPE_VCALENDAR,
	ICALTYPE_VEVENT,
	ICALTYPE_VTODO,
	ICALTYPE_VJOURNAL,
	ICALTYPE_FVREEBUSY,
	ICALTYPE_VTIMEZONE,
	ICALTYPE_VALARM,
	ICALTYPE__MAX
};

enum	icaltztype {
	ICALTZ_DAYLIGHT,
	ICALTZ_STANDARD,
	ICALTZ__MAX
};

enum	icalfreq {
	ICALFREQ_NONE = 0,
	ICALFREQ_SECONDLY,
	ICALFREQ_MINUTELY,
	ICALFREQ_HOURLY,
	ICALFREQ_DAILY,
	ICALFREQ_WEEKLY,
	ICALFREQ_MONTHLY,
	ICALFREQ_YEARLY,
	ICALFREQ__MAX
};

enum	icalwkday {
	ICALWKDAY_NONE = 0,
	ICALWKDAY_SUN,
	ICALWKDAY_MON,
	ICALWKDAY_TUES,
	ICALWKDAY_WED,
	ICALWKDAY_THUR,
	ICALWKDAY_FRI,
	ICALWKDAY_SAT,
	ICALWKDAY__MAX
};

struct	icalnode {
	char		*name;
	char		*param;
	char		*val;
	struct icalnode	*next;
};

struct	icalwk {
	long	 	 wk;
	enum icalwkday	 wkday;
};

enum	icaldatet {
	ICAL_DT_UNSET = 0,
	ICAL_DT_DATETIMEUTC,
	ICAL_DT_DATETIME,
	ICAL_DT_DATE,
};

struct	icaltm {
	time_t		 tm;
	enum icaldatet	 type;
};

struct	icaldur {
	int		 sign; /* >0 pos, <0 neg */
	unsigned long	 day;
	unsigned long	 week;
	unsigned long	 hour;
	unsigned long	 min;
	unsigned long	 sec;
};

#if 0
/*
 * An iCalendar period of time (RFC 2445, 4.3.9).
 * This can be either explicit (bracketed time) or computed (starting
 * bracket and a duration).
 */
struct	icalper {
	struct icaltm	 tm1;
	struct icaldur	 dur; /* if unset, then... */
	struct icaltm	 tm2;
};

/*
 * A repeating date (RFC 2445, 4.8.5.3) is a sequence of finite date
 * components: dates, date-times, or bracketed date spans.
 */
struct	icalrdate {
	int		 set; /* whether set */
	struct icalcomp	*tz; /* time-zone */
	struct icaltm	*dates; /* dates (w/timezone) */
	size_t		 datesz; 
	struct icaltm	*datetimes; /* date-times (w/timezone) */
	size_t		 datesz; 
	struct icalper	*pers; /* date spans, if applicable */
	size_t		 persz;
};
#endif

struct	icalrrule {
	int		 set;
	enum icalfreq	 freq;
	struct icaltm	 until;
	unsigned long	 count;
	unsigned long	 interval;
	unsigned long	*bhr;
	size_t		 bhrsz;
	unsigned long	*bmin;
	size_t		 bminsz;
	long		*bmnd;
	size_t		 bmndsz;
	unsigned long	*bmon;
	size_t		 bmonsz;
	unsigned long	*bsec;
	size_t		 bsecsz;
	long		*bsp;
	size_t		 bspsz;
	struct icalwk	*bwkd;
	size_t		 bwkdsz;
	long		*bwkn;
	size_t		 bwknsz;
	long		*byrd;
	size_t		 byrdsz;
	enum icalwkday	 wkst;
};

struct	icaltz {
	enum icaltztype	 type;
	int		 tzfrom;
	int		 tzto;
	struct icaltm	 dtstart;
	struct icalrrule rrule;
};

struct	icaltime {
	const struct icalcomp *tz;
	struct icaltm	 time;
	char		*tzstr;
};

struct	icalcomp {
	struct icalcomp	*next;
	enum icaltype	 type;
	struct icaltm	 created;
	struct icaltm	 lastmod;
	struct icaltm	 dtstamp;
	struct icalrrule rrule;
	struct icaltime	 dtstart;
	struct icaltime	 dtend;
	struct icaldur	 duration;
	struct icaltz	*tzs;
	size_t		 tzsz;
	const char	*uid;
	const char	*tzid;
};

struct	ical {
	unsigned int	 bits;
#define	ICAL_VCALENDAR	 0x001
#define	ICAL_VEVENT	 0x002
#define	ICAL_VTODO	 0x004
#define	ICAL_VJOURNAL	 0x008
#define	ICAL_VFREEBUSY	 0x010
#define	ICAL_VTIMEZONE	 0x020
#define	ICAL_VALARM	 0x040
	struct icalnode	*first;
	struct icalcomp	*comps[ICALTYPE__MAX];
};

struct	calprop {
	enum calproptype	  key;
	char			 *name;
	char			 *xmlns;
	char			 *val;
	int			  valid;
};

struct	caldav {
	enum calreqtype		  type;
	struct calprop		 *props;
	size_t			  propsz;
	char			**hrefs;
	size_t			  hrefsz;
};

typedef int (*ical_putchar)(int, void *);

__BEGIN_DECLS

struct ical 	 *ical_parse(const char *, const char *, size_t,
			size_t *, char **);
void		  ical_free(struct ical *);
int		  ical_print(const struct ical *, ical_putchar, void *);
int		  ical_printfile(int, const struct ical *);
#if 0
void		  ical_rrule_generate(const struct icaltm *, 
			const struct icalrrule *);
#endif

struct caldav 	 *caldav_parse(const char *, size_t, char **);
void		  caldav_free(struct caldav *);

extern const enum calproptype calprops[CALELEM__MAX];
extern const enum calelem calpropelems[CALPROP__MAX];
extern const char *const calelems[CALELEM__MAX];
extern const char *const icaltypes[ICALTYPE__MAX];
extern const char *const icaltztypes[ICALTZ__MAX];
extern const char *const icalfreqs[ICALFREQ__MAX];
extern const char *const icalwkdays[ICALWKDAY__MAX];

__END_DECLS

#endif
