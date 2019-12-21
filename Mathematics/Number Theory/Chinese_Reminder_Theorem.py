def extended_euclid(a, b):
    if a == 0:
        return b, 0, 1
    else:
        gcd, x, y = extended_euclid(b % a, a)
        return gcd, y - (b // a) * x, x


def chinese_reminder_theorem(A, P):
    if len(A) == 0 or len(A) != len(P):
        return 0, 0

    a1 = A[0]
    m1 = P[0]
    for i in range(1, len(A)):
        a2 = A[i]
        m2 = P[i]
        g = math.gcd(m1, m2)
        if a1 % g != a2 % g:
            return -1, -1
        gcd, p, q = extended_euclid(m1 // g, m2 // g)
        mod = (m1 // g) * m2
        x = (a1 * (m2 // g) * q + a2 * (m1 // g) * p) % mod
        a1 = x
        if a1 < 0:
            a1 += mod
        m1 = mod

    return a1, m1