class Solution {
public:
    double angleClock(int hour, int minutes) {
        double hourAngle = (hour % 12) * 30.0 + 0.5 * minutes;
        double minAngle = minutes * 6;
        double diff = abs(hourAngle - minAngle);
        return min(diff,360 - diff);
    }
};