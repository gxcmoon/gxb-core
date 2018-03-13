/*
    Copyright (C) 2018 gxb

    This file is part of gxb-core.

    gxb-core is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    gxb-core is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with gxb-core.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <graphene/chain/protocol/base.hpp>
#include <graphene/chain/protocol/ext.hpp>

namespace graphene { namespace chain {
    struct  data_storage_params
    {
        account_id_type         from;
        account_id_type         to;
        account_id_type         proxy_account;
        uint16_t                percentage = 0;
        asset                   amount;
        fc::string              memo;
        fc::time_point_sec      expiration;
    };

    struct data_storage_operation : public base_operation {
        struct fee_parameters_type {
            uint64_t fee = GRAPHENE_BLOCKCHAIN_PRECISION / 100;
        };

        fc::string                      proxy_memo;
        asset                           fee;
        data_storage_params             request_params;
        signature_type                  signature;
        extensions_type                 extensions;

        account_id_type fee_payer() const { return request_params.proxy_account; }
        account_id_type get_from_account() const { return request_params.from; }
        account_id_type get_to_account() const { return request_params.to; }
        account_id_type get_proxy_account() const { return request_params.proxy_account; }

        void validate() const
        {
            FC_ASSERT(fee.amount >= 0);
            FC_ASSERT(request_params.amount.amount >= 0);
            FC_ASSERT(proxy_memo.size() > 0);
            FC_ASSERT(get_from_account() != get_to_account());
        }

        share_type calculate_fee(const fee_parameters_type &k) const
        {
            return k.fee;
        }
    };


} } // graphene::chain

FC_REFLECT(graphene::chain::data_storage_params,
            (from)
            (to)
            (proxy_account)
            (amount)
            (percentage)
            (memo)
            (expiration))

FC_REFLECT(graphene::chain::data_storage_operation::fee_parameters_type, (fee))

FC_REFLECT(graphene::chain::data_storage_operation,
            (proxy_memo)
            (fee)
            (request_params)
            (signature)
            (extensions))
