namespace zt {
    namespace SystemGenerator {
        int lastId = 0;

        int registerId() {
            return ++lastId;
        }
    }
}