#ifndef H_AEC
#define H_AEC

namespace ansi{
	inline void setcursor(unsigned int x, unsigned int y){
		printf("\x1b[%u;%uH", y, x);
	}

	inline void clear(){
		printf("\x1b[2J");
	}

	inline void scrollup(unsigned int l){
		printf("\x1b[%uS", l);
	}

	inline void scrolldown(unsigned int l){
		printf("\x1b[%uT", l);
	}

	inline void top(){
		// 128 lines should be enough for anybody
		scrollup(128);
	}
}


#endif//H_AEC
