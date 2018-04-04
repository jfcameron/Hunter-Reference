//
//
//

#ifndef HUNTER_REFERENCE_H
#define HUNTER_REFERENCE_H

namespace hunterreference
{
    /*!
     An object with a secret and a graphics test.
     */
    class object
    {
        int secret = 123;

    public:
        /// gives access to the secret
        int getSecret() const;

        /// runs a neat opengl thing
        void runGraphicsTest();
    };
}

#endif
