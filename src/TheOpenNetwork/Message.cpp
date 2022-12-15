// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Message.h"

namespace TW::TheOpenNetwork {

Cell::Ref Message::intoCell() const {
    CellBuilder builder;

    // info:CommonMsgInfo
    _header->writeTo(builder);

    // init:(Maybe (Either StateInit ^StateInit))
    if (_init.has_value()) {
        builder.appendBitOne(); // Maybe

        builder.appendBitOne(); // Either as ^X
        builder.appendReferenceCell(_init.value().writeTo().intoCell());
    } else {
        builder.appendBitZero();
    }

    // body:(Either X ^X)
    if (_body.has_value()) {
        builder.appendBitOne(); // Either as ^X
        builder.appendReferenceCell(_body.value());
    } else {
        builder.appendBitZero();
    }

    return builder.intoCell();
}

} // namespace TW::TheOpenNetwork
