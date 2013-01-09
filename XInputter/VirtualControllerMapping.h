#include <string>
#include <dinput.h>

//==============================================
// Analog Inputs
struct AnalogInput {
	virtual long AVal(DIJOYSTATE2& js)=0;
};

struct Axis : public AnalogInput {
	Axis(BYTE idx);
	virtual long AVal(DIJOYSTATE2& js);
protected:
	BYTE idx_;
};

struct Slider : public AnalogInput {
	Slider(BYTE idx);
	virtual long AVal(DIJOYSTATE2& js);
protected:
	BYTE idx_;
};

//==============================
// Mappings
struct Mapping {
					Mapping(bool invert, bool flip);
	BYTE			ReadAsTrigger(DIJOYSTATE2& js);
	SHORT			ReadAsAxis(DIJOYSTATE2& js);
	bool			ReadAsButton(DIJOYSTATE2& js);
protected:
	virtual BYTE	AsTrigger(DIJOYSTATE2& js)=0;
	virtual SHORT	AsAxis(DIJOYSTATE2& js)=0;
	virtual bool	AsButton(DIJOYSTATE2& js)=0;

	bool			invert_;
	bool			flip_;
};

//==============================
// Analog Mappings
// Analog
struct AnalogMapping : public Mapping {
	AnalogMapping(AnalogInput* inp, bool invert, bool flip);
	virtual ~AnalogMapping() { delete inp_; }
protected:
	virtual BYTE	AsTrigger(DIJOYSTATE2& js);
	virtual SHORT	AsAxis(DIJOYSTATE2& js);
	virtual bool	AsButton(DIJOYSTATE2& js);
	long			AVal(DIJOYSTATE2 &js);
	AnalogInput*	inp_;
};

// Upper half Analog
struct HalfAnalogMapping : public AnalogMapping {
	HalfAnalogMapping(AnalogInput* inp, bool invert, bool flip);
protected:
	long			AVal(DIJOYSTATE2 &js);
};

//==============================
// Digital mappings
struct DigitalMapping : public Mapping {
protected:
					DigitalMapping(bool invert, bool flip);
	virtual BYTE	AsTrigger(DIJOYSTATE2& js);
	virtual SHORT	AsAxis(DIJOYSTATE2& js);
	virtual bool	AsButton(DIJOYSTATE2& js);
	virtual bool	IsPressed(DIJOYSTATE2 &js)=0;
};

// POV Hats
struct POVMapping : public DigitalMapping {
	enum Position { UP, RIGHT, DOWN, LEFT };

					POVMapping(BYTE idx, bool invert, bool flip, Position pos);
protected:
	virtual bool	IsPressed(DIJOYSTATE2 &js);

	Position pos_;
	BYTE idx_;
};

// Buttons
struct ButtonMapping : public DigitalMapping {
					ButtonMapping(BYTE idx, bool invert, bool flip);
protected:
	virtual bool	IsPressed(DIJOYSTATE2 &js);

	BYTE idx_;
};

