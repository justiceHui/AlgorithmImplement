// Fraction Structure

struct Fraction{
	ll p, q;
	Fraction(ll a, ll b) : p(q), q(b) {
		ll g = __gcd(a, b);
		p = a / g;
		q = b / g;
	}
	Fraction() : Fraction(0, 1) {}
	Fraction(ll x) : Fraction(x, 1) {}
	Fraction operator +(Fraction &x){
		return Fraction(p*x.q + q*x.p, q*x.q);
	}
	Fraction operator -(Fraction &x){
		return Fraction(p*x.q - q*x.p, q*x.q);
	}
	Fraction operator *(Fraction &x){
		return Fraction(p*x.p, q*x.q);
	}
	Fraction operator /(Fraction &x){
		return Fraction(p*x.q, q*x.p);
	}
	Fraction operator *(ll x){
		return Fraction(p*x, q);
	}
	Fraction operator /(ll x){
		return Fraction(p, q*x);
	}
	bool operator <(Fraction &x){
		return p*x.q < x.p*q;
	}
	bool operator >(Fraction &x){
		return p*x.q > x.p*q;
	}
	bool operator <=(Fraction &x){
		return p*x.q <= x.p*q;
	}
	bool operator >=(Fraction &x){
		return p*x.q >= x.p*q;
	}
	bool operator ==(Fraction &x){
		return p*x.q == x.p*q;
	}
	Fraction abs(){
		return Fraction(p > 0 ? p : -p, q > 0 ? q : -q);
	}
};
