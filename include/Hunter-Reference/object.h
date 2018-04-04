//
//
//

#ifndef HUNTER_REFERENCE_H
#define HUNTER_REFERENCE_H

namespace hunterreference
{
    class object
    {
        int secret = 123;

    public:
        int getSecret() const;

        void runGraphicsTest();
    };
}

#endif
