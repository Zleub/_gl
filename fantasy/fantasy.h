#define bool int

typedef struct s_set t_set;
struct s_set {
	bool (*equals)(t_set *);
};
