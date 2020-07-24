#include <QtTest>

#include "../indicators/sevensegments/utils/sevensegmentsutils.h"

#include <pumpkintest.h>

#include <assertions.h>

inline std::ostream& operator<<(std::ostream& os, QPointF const& s)
{
	os << s.x() << ";" << s.y();
	return os;
}


inline std::ostream& operator<<(std::ostream& os, Segment const& s)
{
	os << "Segment(" << s.p1() << ", " << s.p2() << ")";
	return os;
}

class SevenSegmentTest : public PumpkinTest::AutoRegisteredTest
{
public:
	SevenSegmentTest(): PumpkinTest::AutoRegisteredTest("Seven Segment Test")
	{
		test("Segments should be bounded to content rect", []()
		{
			QRectF rect(0, 0, 100, 100);
			auto segments = createSegments(rect);
			for (auto segment: segments)
			{
				PumpkinTest::Assertions::assertTrue(rect.contains(segment.p1()));
				PumpkinTest::Assertions::assertTrue(rect.contains(segment.p2()));
			}
		});

		test("Segments should be shrinked by left", []()
		{
			Segment segment(Orientation::Top, QPointF(0, 0), QPointF(100, 0));
			PumpkinTest::Assertions::assertEquals(Segment(Orientation::Top, QPointF(50, 0), QPointF(100, 0)),
												  segment.fromEnd(0.50));
		});

		test("Segments should be shrinked by right", []()
		{
			Segment segment(Orientation::Top, QPointF(0, 0), QPointF(100, 0));
			PumpkinTest::Assertions::assertEquals(Segment(Orientation::Top, QPointF(0, 0), QPointF(50, 0)),
												  segment.fromStart(0.50));
		});

		test("Segments should be shrinked by middle", []()
		{
			Segment segment(Orientation::Top, QPointF(0, 0), QPointF(100, 0));
			PumpkinTest::Assertions::assertEquals(Segment(Orientation::Top, QPointF(25.0, 0), QPointF(75.0, 0)),
												  segment.fromMiddle(0.50));
		});
	}
};

REGISTER_TEST(SevenSegmentTest)
